#define SOPLEX_WITH_GMP
#include <fenv.h>
#include <fstream>
#include <math.h>
#include <memory>
#include <random>
#include <soplex.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TRIES 100
#define VIOLATE_THRESHOLD 20
#define SAMPLE_MATCH_THRESHOLD 20
#define MAX_ITERATIONS 1200

#pragma STDC FENV_ACCESS ON

#ifdef EXIT_ON_THRESHOLD
const int RLIBM_EXIT_ON_THRESHOLD = 1;
#else
const int RLIBM_EXIT_ON_THRESHOLD = 0;
#endif

using namespace soplex;
using namespace std;

size_t prev_successful_degree = 0;

typedef union {
  double d;
  uint64_t x;
} double_x;

typedef struct {
  double x;         /* original input */
  double lb;        /* lower bound */
  double ub;        /* upper bound */
  double w;         /* weight */
  double u;         /* uniform random value */
} interval_data;

typedef struct{
  double x;
  double lb;
  double ub;
  double orig_lb;  /* remember lb before narrowing */
  double orig_ub;  /* remember ub before narrowing */
  double w;
  double u;
  double k;        /* key computed as 1/u^w */

} sample_data;

typedef struct{
  double key;
  size_t index;
} sample_info;

typedef struct {
  int termsize;
  int* power;
  double* coeffs;
} polynomial;

static inline double rndu_add(double a, double b)
{
  double neg_sum = (-a)+(-b);
  return -neg_sum;
}

static inline double rndu_multiply(double a, double b)
{
  double neg_prod = -a*b;
  return -neg_prod;
}

polynomial* rlibm_solve_with_soplex(sample_data* sintervals,
				    size_t ssize, int* power, int termsize){
  
  SoPlex mysoplex;
  mysoplex.setBoolParam(SoPlex::RATFACJUMP,true);
  mysoplex.setIntParam(SoPlex::SOLVEMODE,2);
  mysoplex.setIntParam(SoPlex::CHECKMODE,2);
  mysoplex.setIntParam(SoPlex::SYNCMODE,1);
  mysoplex.setIntParam(SoPlex::READMODE,1);
  mysoplex.setRealParam(SoPlex::FEASTOL,0.0);
  mysoplex.setRealParam(SoPlex::OPTTOL,0.0);
  mysoplex.setRealParam(SoPlex::EPSILON_ZERO,0.0);
  mysoplex.setRealParam(SoPlex::EPSILON_FACTORIZATION,0.0);
  mysoplex.setRealParam(SoPlex::EPSILON_UPDATE,0.0);
  mysoplex.setRealParam(SoPlex::EPSILON_PIVOT,0.0);
  mysoplex.setIntParam(SoPlex::VERBOSITY,0);
  mysoplex.setRealParam(SoPlex::TIMELIMIT,5*60);
  
  /* we first add objective variables */
  DSVectorRational dummycol(0);
  for(int i=0;i<termsize;i++){
    auto column=LPColRational(1.0,dummycol,infinity,-infinity);
    mysoplex.addColRational(column);
  }
  
  /* then add constraints one by one */
  for(int i = 0; i < ssize; i++){
    Rational xValR(sintervals[i].x);
    DSVectorRational row1(termsize);
    
    for(int j=0; j<termsize;j++){
      Rational toAdd(1.0);
      for(int k=0;k<power[j];k++) toAdd*=xValR;

      row1.add(j,toAdd);
    }
        
    // LPRow: low bound, row, upper bound
    double lbnd = sintervals[i].lb;
    double ubnd = sintervals[i].ub;
    mysoplex.addRowRational(LPRowRational(lbnd,row1,ubnd));
  }

  /* solve LP */
  SPxSolver::Status stat;
  stat=mysoplex.optimize();
  
  /* get solution */
  if(stat==SPxSolver::OPTIMAL){
    DVectorRational prim(termsize);
    mysoplex.getPrimalRational(prim);

    /* generate the polynomial as a plain structure */
    polynomial* p = (polynomial *) calloc(1, sizeof(polynomial));
    p->termsize = termsize;
    p->power = power;
    p->coeffs = (double *) calloc(termsize, sizeof(double));
    
    for(int i=0;i<termsize;i++)
      p->coeffs[i] = mpq_get_d(*(prim[i].getMpqPtr_w()));

    return p;
  }
  else if(stat==SPxSolver::UNBOUNDED){

    polynomial* p = (polynomial *) calloc(1, sizeof(polynomial));
    p->termsize = termsize;
    p->power = power;
    p->coeffs = (double *) calloc(termsize, sizeof(double));
    
    for(int i=0;i<termsize;i++)
      p->coeffs[i] = 0.0;
    
    return p;
  }
  
  return nullptr;
}

void check_sorted(sample_info* sampled_indices, size_t ssize){
  double min= sampled_indices[0].key;

  for(size_t i = 0; i< ssize; i++){
    assert ( min <= sampled_indices[i].key);
    min = sampled_indices[i].key;
  }
  
}

bool rlibm_poly_evaluation(double x, polynomial* poly, double& poly_lb, double& poly_ub){
  if(poly->termsize == 3) {
    //x2
    double x2_min = x*x;
    double x2_max = rndu_multiply(x, x);
    //c2*x2
    double c2_x2_min_d = x2_min*poly->coeffs[2];
    double c2_x2_max_d = x2_max*poly->coeffs[2];
    double m1_min = min(c2_x2_min_d, c2_x2_max_d);
    double c2_x2_min_u = rndu_multiply(x2_min, poly->coeffs[2]);
    double c2_x2_max_u = rndu_multiply(x2_max, poly->coeffs[2]);
    double m1_max = max(c2_x2_min_u, c2_x2_max_u);
    //c2*x2+c1
    double p1_min = m1_min+poly->coeffs[1];
    double p1_max = rndu_add(m1_max, poly->coeffs[1]);
    //(c2*x2+c1)*x2
    double p1_min_x2_min_d = p1_min*x2_min;
    double p1_min_x2_max_d = p1_min*x2_max;
    double p1_max_x2_min_d = p1_max*x2_min;
    double p1_max_x2_max_d = p1_max*x2_max;
    double m2_min = min(p1_min_x2_min_d, min(p1_min_x2_max_d, min(p1_max_x2_min_d, p1_max_x2_max_d)));  
    double p1_min_x2_min_u = rndu_multiply(p1_min, x2_min);
    double p1_min_x2_max_u = rndu_multiply(p1_min, x2_max);
    double p1_max_x2_min_u = rndu_multiply(p1_max, x2_min);
    double p1_max_x2_max_u = rndu_multiply(p1_max, x2_max);
    double m2_max = max(p1_min_x2_min_u, max(p1_min_x2_max_u, max(p1_max_x2_min_u, p1_max_x2_max_u)));
    //(c2*x2+c1)*x2+c0
    double p2_min = m2_min+poly->coeffs[0];
    double p2_max = rndu_add(m2_max, poly->coeffs[0]);
    if (poly->power[2] == 5) { 
      //((c2*x2+c1)*x2+c0)*x
      double p2_min_x_d = p2_min*x;
      double p2_max_x_d = p2_max*x;
      double m3_min = min(p2_min_x_d, p2_max_x_d);
      double p2_min_x_u = rndu_multiply(p2_min, x);
      double p2_max_x_u = rndu_multiply(p2_max, x);
      double m3_max = max(p2_min_x_u, p2_max_x_u);
      poly_lb = m3_min;
      poly_ub = m3_max;
    } else {
      poly_lb = p2_min;
      poly_ub = p2_max;
    }
    return true;
  } else if (poly->termsize == 4) {
    //x2
    double x2_min = x*x;
    double x2_max = rndu_multiply(x,x);
    double m1_min = x*poly->coeffs[1]; 
    double m1_max = rndu_multiply(x,poly->coeffs[1]); 
    double m2_min = x*poly->coeffs[3]; 
    double m2_max = rndu_multiply(x,poly->coeffs[3]);
    //c1*x+c0
    double p1_min = m1_min+poly->coeffs[0];
    double p1_max = rndu_add(m1_max, poly->coeffs[0]);
    //c3*x+c2
    double p2_min = m2_min+poly->coeffs[2];
    double p2_max = rndu_add(m2_max, poly->coeffs[2]);
    //(c3*x+c2)*x2+c0
    double p2_min_x2_min_d = x2_min*p2_min;
    double p2_min_x2_max_d = x2_max*p2_min;
    double p2_max_x2_min_d = x2_min*p2_max;
    double p2_max_x2_max_d = x2_max*p2_max;
    double m3_min = min(p2_min_x2_min_d, min(p2_min_x2_max_d, min(p2_max_x2_min_d, p2_max_x2_max_d)));
    double p2_min_x2_min_u = rndu_multiply(x2_min,p2_min);
    double p2_min_x2_max_u = rndu_multiply(x2_max,p2_min);
    double p2_max_x2_min_u = rndu_multiply(x2_min,p2_max);
    double p2_max_x2_max_u = rndu_multiply(x2_max,p2_max);
    double m3_max = max(p2_min_x2_min_u, max(p2_min_x2_max_u, max(p2_max_x2_min_u, p2_max_x2_max_u)));
    double p3_min = m3_min+p1_min;
    double p3_max = rndu_add(m3_max, p1_max);
    //(c3*x+c2)*x2+c0)*x
    double p3_min_x_d = p3_min*x;
    double p3_max_x_d = p3_max*x;
    double m4_min = min(p3_min_x_d, p3_max_x_d);
    double p3_min_x_u = rndu_multiply(p3_min, x);
    double p3_max_x_u = rndu_multiply(p3_max, x);
    double m4_max = max(p3_min_x_u, p3_max_x_u);
    poly_lb = m4_min;
    poly_ub = m4_max;
    return true;
  } else if (poly->termsize == 5) {
    if (poly->power[4] == 5) {
      //x2
      double x2_min = x*x;
      double x2_max = rndu_multiply(x, x);
      double m1_min = x*poly->coeffs[2];
      double m1_max = rndu_multiply(x, poly->coeffs[2]);
      double m2_min = x*poly->coeffs[4];
      double m2_max = rndu_multiply(x, poly->coeffs[4]);
      //(c2*x+c1)
      double p1_min = m1_min + poly->coeffs[1];
      double p1_max = rndu_add(m1_max, poly->coeffs[1]);
      //(c4*x+c3)
      double p2_min = m2_min + poly->coeffs[3];
      double p2_max = rndu_add(m2_max, poly->coeffs[3]);
      //(c4*x+c3)*x2+(c2*x+c1)
      double p2_min_x2_min_d = p2_min*x2_min;
      double p2_min_x2_max_d = p2_min*x2_max;
      double p2_max_x2_min_d = p2_max*x2_min;
      double p2_max_x2_max_d = p2_max*x2_max;
      double m3_min = min(p2_min_x2_min_d, min(p2_min_x2_max_d, min(p2_max_x2_min_d, p2_max_x2_max_d)));
      double p2_min_x2_min_u = rndu_multiply(p2_min, x2_min);
      double p2_min_x2_max_u = rndu_multiply(p2_min, x2_max);
      double p2_max_x2_min_u = rndu_multiply(p2_max, x2_min);
      double p2_max_x2_max_u = rndu_multiply(p2_max, x2_max);
      double m3_max = max(p2_min_x2_min_u, max(p2_min_x2_max_u, max(p2_max_x2_min_u, p2_max_x2_max_u)));
      double p3_min = m3_min + p1_min;
      double p3_max = rndu_add(m3_max, p1_max);
      //((c4*x+c3)*x2+(c2*x+c1))*x2
      double p3_min_x2_min_d = p3_min*x2_min;
      double p3_min_x2_max_d = p3_min*x2_max;
      double p3_max_x2_min_d = p3_max*x2_min;
      double p3_max_x2_max_d = p3_max*x2_max;
      double m4_min = min(p3_min_x2_min_d, min(p3_min_x2_max_d, min(p3_max_x2_min_d, p3_max_x2_max_d)));
      double p3_min_x2_min_u = rndu_multiply(p3_min, x2_min);
      double p3_min_x2_max_u = rndu_multiply(p3_min, x2_max);
      double p3_max_x2_min_u = rndu_multiply(p3_max, x2_min);
      double p3_max_x2_max_u = rndu_multiply(p3_max, x2_max);
      double m4_max = max(p3_min_x2_min_u, max(p3_min_x2_max_u, max(p3_max_x2_min_u, p3_max_x2_max_u)));
      //c0*x
      double m5_min = x*poly->coeffs[0];
      double m5_max = rndu_multiply(x, poly->coeffs[0]);
      //((c4*x+c3)*x2+(c2*x+c1))*x2+c0*x
      double p4_min = m4_min+m5_min;
      double p4_max = rndu_add(m4_max, m5_max);
      poly_lb = p4_min;
      poly_ub = p4_max;
    } else {
      //x2
      double x2_min = x*x;
      double x2_max = rndu_multiply(x,x);
      //c1*x
      double m1_min = x*poly->coeffs[1];
      double m1_max = rndu_multiply(x,poly->coeffs[1]);
      //c3*x
      double m2_min = x*poly->coeffs[3];
      double m2_max = rndu_multiply(x,poly->coeffs[3]);
      //c4*x2
      double c4_x2_min_d = x2_min*poly->coeffs[4];
      double c4_x2_max_d = x2_max*poly->coeffs[4];
      double m3_min = min(c4_x2_min_d, c4_x2_max_d);
      double c4_x2_min_u = rndu_multiply(x2_min, poly->coeffs[4]);
      double c4_x2_max_u = rndu_multiply(x2_max, poly->coeffs[4]);
      double m3_max = max(c4_x2_min_u, c4_x2_max_u);
      //c1*x+c0
      double p1_min = m1_min + poly->coeffs[0];
      double p1_max = rndu_add(m1_max, poly->coeffs[0]);
      //c3*x+c2
      double p2_min = m2_min + poly->coeffs[2];
      double p2_max = rndu_add(m2_max, poly->coeffs[2]);
      //c4*x2+(c3*x+c2)
      double p3_min = m3_min + p2_min;
      double p3_max = rndu_add(m3_max, p2_max);
      //(c4*x2+(c3*x+c2))*x2
      double p3_min_x2_min_d = p3_min*x2_min;
      double p3_min_x2_max_d = p3_min*x2_max;
      double p3_max_x2_min_d = p3_max*x2_min;
      double p3_max_x2_max_d = p3_max*x2_max;
      double m4_min = min(p3_min_x2_min_d, min(p3_min_x2_max_d, min(p3_max_x2_min_d, p3_max_x2_max_d)));
      double p3_min_x2_min_u = rndu_multiply(p3_min, x2_min);
      double p3_min_x2_max_u = rndu_multiply(p3_min, x2_max);
      double p3_max_x2_min_u = rndu_multiply(p3_max, x2_min);
      double p3_max_x2_max_u = rndu_multiply(p3_max, x2_max);
      double m4_max = max(p3_min_x2_min_u, max(p3_min_x2_max_u, max(p3_max_x2_min_u, p3_max_x2_max_u)));
      //(c4*x2+(c3*x+c2))*x2+(c1*x+c0)
      double p4_min = m4_min + p1_min;
      double p4_max = rndu_add(m4_max, p1_max);
      poly_lb = p4_min;
      poly_ub = p4_max;
    }
    return true;
  } else if (poly->termsize == 6) {
    //x2
    double x2_min = x*x;
    double x2_max = rndu_multiply(x,x);
    //c1*x+c0
    double m1_min = poly->coeffs[1]*x;
    double m1_max = rndu_multiply(poly->coeffs[1], x);
    double p1_min = m1_min + poly->coeffs[0];
    double p1_max = rndu_add(m1_max, poly->coeffs[0]);
    //c3*x+c2
    double m2_min = poly->coeffs[3]*x;
    double m2_max = rndu_multiply(poly->coeffs[3], x);
    double p2_min = m2_min + poly->coeffs[2];
    double p2_max = rndu_add(m2_max, poly->coeffs[2]);
    //c5*x+c4
    double m3_min = poly->coeffs[5]*x;
    double m3_max = rndu_multiply(poly->coeffs[5], x);
    double p3_min = m3_min + poly->coeffs[4];
    double p3_max = rndu_add(m3_max, poly->coeffs[4]);
    //(c5*x+c4)*x2
    double p3_min_x2_min_d = p3_min*x2_min;
    double p3_min_x2_max_d = p3_min*x2_max;
    double p3_max_x2_min_d = p3_max*x2_min;
    double p3_max_x2_max_d = p3_max*x2_max;
    double m4_min = min(p3_min_x2_min_d, min(p3_min_x2_max_d, min(p3_max_x2_min_d, p3_max_x2_max_d)));
    double p3_min_x2_min_u = rndu_multiply(p3_min, x2_min);
    double p3_min_x2_max_u = rndu_multiply(p3_min, x2_max);
    double p3_max_x2_min_u = rndu_multiply(p3_max, x2_min);
    double p3_max_x2_max_u = rndu_multiply(p3_max, x2_max);
    double m4_max = max(p3_min_x2_min_u, max(p3_min_x2_max_u, max(p3_max_x2_min_u, p3_max_x2_max_u)));
    //(c5*x+c4)*x2+(c3*x+c2)
    double p4_min = m4_min+p2_min;
    double p4_max = rndu_add(m4_max, p2_max);
    //((c5*x+c4)*x2+(c3*x+c2))*x2
    double p4_min_x2_min_d = p4_min*x2_min;
    double p4_min_x2_max_d = p4_min*x2_max;
    double p4_max_x2_min_d = p4_max*x2_min;
    double p4_max_x2_max_d = p4_max*x2_max;
    double m5_min = min(p4_min_x2_min_d, min(p4_min_x2_max_d, min(p4_max_x2_min_d, p4_max_x2_max_d)));
    double p4_min_x2_min_u = rndu_multiply(p4_min, x2_min);
    double p4_min_x2_max_u = rndu_multiply(p4_min, x2_max);
    double p4_max_x2_min_u = rndu_multiply(p4_max, x2_min);
    double p4_max_x2_max_u = rndu_multiply(p4_max, x2_max);
    double m5_max = max(p4_min_x2_min_u, max(p4_min_x2_max_u, max(p4_max_x2_min_u, p4_max_x2_max_u)));
    //((c5*x+c4)*x2+(c3*x+c2))*x2+(c1*x+c0)
    double p5_min = m5_min+p1_min;
    double p5_max = m5_max+p1_max;
    poly_lb = p5_min;
    poly_ub = p5_max;
    return true;
  }
  printf("should not come here\n");
  exit(0);
}

bool rlibm_validate_and_fix_intervals(sample_data* sintervals,
				      size_t ssize, polynomial* poly){

  bool return_val = true;
  for(size_t i = 0; i < ssize; i++){
    double y_lb, y_ub;
    bool check_poly = rlibm_poly_evaluation(sintervals[i].x, poly, y_lb, y_ub);
    if (!check_poly) {
      return_val = false;
      continue;
    }
    if(y_lb > sintervals[i].orig_ub){
      return_val = false;
      double_x lbx;
      lbx.d = sintervals[i].lb;
      if(lbx.d >= 0) {
	lbx.x = lbx.x - 1;
      }
      else{
	lbx.x = lbx.x + 1 ;
      }
      sintervals[i].lb = lbx.d;
    } else if(y_lb < sintervals[i].orig_lb){
      return_val = false;
      double_x lbx;
      lbx.d = sintervals[i].lb;
      if(lbx.d >= 0) {
	lbx.x = lbx.x + 1;
      }
      else{
	lbx.x = lbx.x - 1 ;
      }
      sintervals[i].lb = lbx.d;
    }
    if(y_ub < sintervals[i].orig_lb){
      return_val = false;
      double_x ubx;
      ubx.d = sintervals[i].ub;
      if(ubx.d >= 0){
	ubx.x = ubx.x + 1;
      }
      else {
	ubx.x = ubx.x - 1;
      }
      sintervals[i].ub = ubx.d;
    } else if(y_ub > sintervals[i].orig_ub){
      return_val = false;
      double_x ubx;
      ubx.d = sintervals[i].ub;
      if(ubx.d >= 0){
	ubx.x = ubx.x - 1;
      }
      else {
	ubx.x = ubx.x + 1;
      }
      sintervals[i].ub = ubx.d;
    }
  }
  return return_val;
}

// memory leak on the polynomial

polynomial*
rlibm_generate_polynomial(sample_data* sintervals, size_t ssize,
			  int* power, int power_size, int max_tries){

  for(int i = power_size - 1; i < power_size; i++){
    printf("Trying to generate a polynomial  with %d terms \n", i+1);

    int count = 0;
    while(count < max_tries){
      polynomial* p = rlibm_solve_with_soplex(sintervals, ssize, power, i+1);
      if(p && rlibm_validate_and_fix_intervals(sintervals, ssize, p)){
	prev_successful_degree = i;
	return p;
      }
      if(p != nullptr){
	free(p);
      }
      count++;
    }    
  }
  return nullptr;

}

int sample_compare(const void* s1, const void* s2){

  sample_info* e1 = (sample_info*) s1;
  sample_info* e2 = (sample_info*) s2;
  return e1->key > e2->key;
}

void rlibm_print_sample(sample_info* sampled_indices, size_t size){

  double prev = 0.0;
  for(size_t i = 0; i < size; i++){
    assert(sampled_indices[i].key >= prev);
    prev = sampled_indices[i].key;
    printf("counter=%lu, key=%e, sample_index=%lu\n", i, sampled_indices[i].key,
	   sampled_indices[i].index);
  }
}

void rlibm_weighted_random_sample(sample_info* sampled_indices, size_t ssize,
				  interval_data* intervals, size_t nentries){

  for(size_t i = 0; i < ssize; i++){
    sampled_indices[i].key = pow(intervals[i].u, 1./(intervals[i].w));
    sampled_indices[i].index = i;
  }
  
  qsort(sampled_indices, ssize, sizeof(sample_info), sample_compare);
  //  check_sorted (sampled_indices, ssize);

  /* select the top ssize indices from the entire interval data */
  
  for(size_t i = ssize; i < nentries; i++){

    /* if the ith element is smaller than the least element in the
       sample, then nothing to do */
    size_t j= 0;

    double interval_key = pow(intervals[i].u, 1./(intervals[i].w));
    
    if(interval_key > sampled_indices[0].key){
      /* do insertion sort of the data */
      while(interval_key > sampled_indices[j].key && j < ssize) j++;

      for(size_t t=1; t < j; t++) {
	sampled_indices[t-1] = sampled_indices[t];
      }
      sampled_indices[j-1].key = interval_key;
      sampled_indices[j-1].index = i;
    }
  }
  //  check_sorted(sampled_indices, ssize);
}


size_t rlibm_compute_violated_indices(size_t* violated_indices, interval_data* intervals, size_t nentries, polynomial* poly){

  size_t num_violated_indices = 0;
  for(size_t i = 0; i < nentries; i++){
    double y_lb, y_ub;
    rlibm_poly_evaluation(intervals[i].x, poly, y_lb, y_ub);
    if (y_lb < intervals[i].lb || y_lb > intervals[i].ub || y_ub < intervals[i].lb || y_ub > intervals[i].ub){
      violated_indices[num_violated_indices] = i;
      num_violated_indices++;
    }
  }
  return num_violated_indices;
}

void rlibm_evaluate_and_update_weights(size_t* violated_indices, size_t num_violated_indices,
				       interval_data* intervals, size_t nentries, size_t d){
  double w_v = 0.0;
  double w_s = 0.0;

  // this can be optimized to only change the updated weights. For now
  // using an inefficient one
  for (size_t i = 0; i < nentries; i++){
    w_s = w_s + intervals[i].w;
  }

  for(size_t i = 0; i < num_violated_indices; i++){
    w_v = w_v + intervals[violated_indices[i]].w;
  }

  //doubling the weights for a lucky iteration
  if(w_v <= 2 * w_s / (9*d -1)){
    for(size_t i = 0; i < num_violated_indices; i++){
      size_t vindex = violated_indices[i];
      intervals[vindex].w  = intervals[vindex].w * 2;
    }
  }  
}

void
rlibm_regenerate_random_values_and_reset_weights(interval_data* intervals,
						 size_t nentries){

  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for(size_t i = 0; i < nentries; i++){
    intervals[i].u = distribution(generator);
    intervals[i].w = 1.0;
  }
}

bool check_sampled_indices(sample_info* sample, sample_info* prev_sample, size_t size){

  for(size_t i =0; i < size; i++){
    if (sample[i].index != prev_sample[i].index){
      return false;
    }
  }
  return true;
}

void rlibm_print_polyinfo(polynomial* p){

  if(p->termsize == 0){
    printf("Polynomial has no terms!\n");
    exit(0);
  }

  printf("Polynomial: y=%a x^(%d)",p->coeffs[0],p->power[0]);
  for(int j=1;j<p->termsize;j++){
    printf(" + %a x^(%d)",p->coeffs[j],p->power[j]);
  }
  printf("\n");

}

int main(int argc, char** argv){

  if(argc != 2){
    printf("Usage: %s <interval file> \n", argv[0]);
    exit(0);
  }

  printf("EXIT_ON_THRESHOLD is %d\n", RLIBM_EXIT_ON_THRESHOLD);
  
  FILE* fp = fopen(argv[1], "r");
  assert(fp != nullptr);

  /* count the number of entries */

  fseek(fp, 0, SEEK_END);
  unsigned long nentries = ftell(fp);
  nentries = nentries/(3*sizeof(double));
  printf("number of intervals = %lu\n", nentries);
  fseek(fp, 0, SEEK_SET);
  fesetround(FE_DOWNWARD);

  interval_data* intervals = (interval_data*) calloc(nentries, sizeof(interval_data));

  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (unsigned long i = 0; i < nentries; i++){
    double data_entry[3];
    size_t bytes = fread(data_entry, sizeof(double), 3, fp);
    intervals[i].w = 1.0;
    intervals[i].u = distribution(generator);
    intervals[i].x = data_entry[0];
    intervals[i].lb = data_entry[1];
    intervals[i].ub = data_entry[2];
  }

  int powers[] = {0, 2, 4}; //cos small case + cos for cos, cosh, cospi, sin, sinh, sinpi
  //int powers[] = {1, 3, 5}; //sin small case + sin for cos, cosh, cospi, sin, sinh, sinpi
  //int powers[] = {0, 1, 2, 3, 4}; //exp
  //int powers[] = {0, 1, 2, 3, 4, 5}; //exp2, exp10
  //int powers[] = {1, 2, 3, 4} //log, log10 
  //int powers[] = {1, 2, 3, 4, 5}; //log2 

  int powers_size = sizeof(powers)/sizeof(powers[0]);

  /* sample size */

  size_t cd = 9 * powers_size * powers_size;
  size_t samplesize = cd;

  size_t n_violated_indices = 0;
  size_t *violated_indices = (size_t *) calloc(nentries, sizeof(size_t));

  sample_info* sampled_indices = (sample_info*) calloc(cd, sizeof(sample_info));

  size_t prev_violated_indices = 0;
  size_t matched_violated_indices = 0;

  sample_data* sampled_intervals = (sample_data *) calloc(cd, sizeof(sample_data));
  
  polynomial* p = nullptr;
  size_t total_iterations = 0;

  do{
    if(p != nullptr) free(p);
    
    n_violated_indices = 0;
    
    rlibm_weighted_random_sample(sampled_indices, cd, intervals, nentries);    
    total_iterations++;
    
    for (size_t i = 0; i < cd; i++){
      size_t iindex = sampled_indices[i].index;
      
      sampled_intervals[i].x = intervals[iindex].x;
      sampled_intervals[i].lb = intervals[iindex].lb;
      sampled_intervals[i].ub = intervals[iindex].ub;
      sampled_intervals[i].orig_lb = sampled_intervals[i].lb;
      sampled_intervals[i].orig_ub = sampled_intervals[i].ub;
      sampled_intervals[i].w = intervals[iindex].w;
      sampled_intervals[i].u = intervals[iindex].u;
      sampled_intervals[i].k = sampled_indices[i].key;
    }

    /* need to implement these functions */
    p = rlibm_generate_polynomial(sampled_intervals, samplesize, powers, powers_size, MAX_TRIES);

    if(p){
      n_violated_indices = rlibm_compute_violated_indices(violated_indices, intervals, nentries, p);
      printf("number of violated intervals: %lu, total iterations=%lu \n", n_violated_indices, total_iterations);

      if(n_violated_indices <= VIOLATE_THRESHOLD){
	printf("VIOLATING INPUTS BELOW THRESHOLD:\n");
	for(size_t m = 0; m < n_violated_indices; m++){
	  if (m) printf(", ");
	  printf("%a", intervals[violated_indices[m]].x);
	  if (m==n_violated_indices-1) printf("\n");
	}
	rlibm_print_polyinfo(p);
	if(RLIBM_EXIT_ON_THRESHOLD){
	  break;
	}
      }
      
      rlibm_evaluate_and_update_weights(violated_indices, n_violated_indices, intervals, nentries, powers_size);

    }
    else {
      if(total_iterations > MAX_ITERATIONS){
	printf("total iterations exceeded %d, terminating the polynomial geenerator\n", MAX_ITERATIONS);
	if(p!= nullptr){
	  free(p);
	  p = nullptr;	  
	}
	break;
      }
      printf("failed to generate polynomial, resetting weights, total_iterations=%lu\n", total_iterations);
      //prev_successful_degree = 0;      
      rlibm_regenerate_random_values_and_reset_weights(intervals, nentries);
    }

    /* debugging feature to reset weights for the sample if not making progress*/
    if(n_violated_indices != 0 && (prev_violated_indices == n_violated_indices)){
      matched_violated_indices++;
      if(matched_violated_indices > SAMPLE_MATCH_THRESHOLD){
	matched_violated_indices = 0;
	n_violated_indices = 0;
	
	printf("not making progress, same number of violated indices, resetting weights, total_iterations=%lu\n", total_iterations);
	prev_successful_degree = 0;
	rlibm_regenerate_random_values_and_reset_weights(intervals, nentries);
	if(p!= nullptr) {
	  free(p);
	  p = nullptr;
	}
	continue;
      }
    }
    else{
      matched_violated_indices = 0;
      prev_violated_indices = n_violated_indices;
    }    
  } while(n_violated_indices > 0 || !p);

  if(p){
    rlibm_print_polyinfo(p);
  }
  else {
    printf("Could not generate the polynomial that satisifies all intervals, check for partial results with a few violated intervals\n");
  }
  
  fclose(fp);
  free(p);
  free(sampled_intervals);
  free(sampled_indices);
  free(intervals);
  free(violated_indices);
  
  return 0;

}
