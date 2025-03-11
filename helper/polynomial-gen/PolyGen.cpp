#include "PolyGen.hpp"

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

polynomial* PolyFinder::solve_with_soplex(sample_data* sintervals, size_t ssize, int* power, int termsize) {
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
    double lbnd= sintervals[i].lb;
    double ubnd= sintervals[i].ub;
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

double PolyFinder::poly_horner_evaluation(double x, polynomial* poly){

  double ret_val = 0.0;

  // simulated Horner's method
  for(int i = poly->termsize-1; i> 0; i--){
    ret_val = ret_val + poly->coeffs[i];
    double xmul = 1.0;
    for(int j = 0; j < (poly->power[i] - poly->power[i-1]); j++){
      xmul = xmul * x;
    }
    ret_val = ret_val * xmul;	  
  }
  ret_val = ret_val + poly->coeffs[0];
  
  for(int j = 0; j < poly->power[0]; j++){
    ret_val = ret_val * x;
  }  
  return ret_val;
}

double PolyFinder::poly_evaluation(double x, polynomial* poly) {
  if (poly->termsize == 3) {
    if (poly->power[2] == 5) {
      double x2 = x*x;
      double tmp = x2*poly->coeffs[2]+poly->coeffs[1];
      return x*(x2*tmp+poly->coeffs[0]);
    } else {
      double x2 = x*x;
      double tmp = x2*poly->coeffs[2]+poly->coeffs[1];
      return x2*tmp+poly->coeffs[0];
    } 
  } else if (poly->termsize == 4) { 
    if (poly->power[3] == 4) {
      double x2 = x*x;
      double tmp1 = x*poly->coeffs[1]+poly->coeffs[0];
      double tmp2 = x*poly->coeffs[3]+poly->coeffs[2];
      double tmp3 = x2*tmp2+tmp1;
      return x*tmp3;
    } else { 
      double x2 = x*x;
      double tmp1 = x*poly->coeffs[1]+poly->coeffs[0];
      double tmp2 = x*poly->coeffs[3]+poly->coeffs[2];
      double tmp3 = x2*tmp2+tmp1;
      return tmp3;
    } 
  } else if (poly->termsize == 5) {
    if (poly->power[4] == 5) {
      double x2 = x*x;
      double tmp1 = x*poly->coeffs[4]+poly->coeffs[3];
      double tmp2 = x*poly->coeffs[2]+poly->coeffs[1];
      double tmp3 = x2*tmp1+tmp2;
      double tmp4 = x2*tmp3;
      double tmp5 = x*poly->coeffs[0];
      return tmp4+tmp5;
    } else {
      double x2 = x*x;
      double tmp1 = x*poly->coeffs[1]+poly->coeffs[0];
      double tmp2 = x*poly->coeffs[3]+poly->coeffs[2];
      double tmp3 = x2*poly->coeffs[4]+tmp2;
      double tmp4 = x2*tmp3+tmp1;
      return tmp4;
    }
  } else if (poly->termsize==6) { 
    double x2 = x*x;
    double tmp1 = poly->coeffs[1]*x+poly->coeffs[0];
    double tmp2 = poly->coeffs[3]*x+poly->coeffs[2];
    double tmp3 = poly->coeffs[5]*x+poly->coeffs[4];
    double tmp4 = tmp3*x2+tmp2;
    double tmp5 = tmp4*x2+tmp1;
    return tmp5;
  } 
  return poly_horner_evaluation(x,poly);
}

bool PolyFinder::poly_evaluation_multi(double x, polynomial* poly, double& poly_lb, double& poly_ub) {
  if (poly->termsize == 1){
    if (poly->power[0] == 0) {
      poly_lb = poly->coeffs[0];
      poly_ub = poly->coeffs[0];
    } else {
      poly_lb = x*poly->coeffs[0];
      poly_ub = rndu_multiply(x, poly->coeffs[0]);
    }
    return true;
  } else if(poly->termsize == 2) {
    double x2_min = x*x;
    double x2_max = rndu_multiply(x, x);
    double c1_x2_min_d = x2_min*poly->coeffs[1];
    double c1_x2_max_d = x2_max*poly->coeffs[1];
    double m1_min = min(c1_x2_min_d, c1_x2_max_d);
    double c1_x2_min_u = rndu_multiply(x2_min, poly->coeffs[1]);
    double c1_x2_max_u = rndu_multiply(x2_max, poly->coeffs[1]);
    double m1_max = max(c1_x2_min_u, c1_x2_max_u);
    double p1_min = m1_min+poly->coeffs[0];
    double p1_max = rndu_add(m1_max, poly->coeffs[0]);
    if (poly->power[1] == 3) {
      double p1_min_x_d = p1_min*x;
      double p1_max_x_d = p1_max*x;
      double m2_min = min(p1_min_x_d, p1_max_x_d);
      double p1_min_x_u = rndu_multiply(p1_min, x);
      double p1_max_x_u = rndu_multiply(p1_max, x);
      double m2_max = max(p1_min_x_u, p1_max_x_u);
      poly_lb = m2_min;
      poly_ub = m2_max;
    } else {
      poly_lb = p1_min;
      poly_ub = p1_max;
    } 
    return true;
  } else if(poly->termsize == 3) {
    double x2_min = x*x;
    double x2_max = rndu_multiply(x, x);
    double c2_x2_min_d = x2_min*poly->coeffs[2];
    double c2_x2_max_d = x2_max*poly->coeffs[2];
    double m1_min = min(c2_x2_min_d, c2_x2_max_d);
    double c2_x2_min_u = rndu_multiply(x2_min, poly->coeffs[2]);
    double c2_x2_max_u = rndu_multiply(x2_max, poly->coeffs[2]);
    double m1_max = max(c2_x2_min_u, c2_x2_max_u);
    double p1_min = m1_min+poly->coeffs[1];
    double p1_max = rndu_add(m1_max, poly->coeffs[1]);
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
    double p2_min = m2_min+poly->coeffs[0];
    double p2_max = rndu_add(m2_max, poly->coeffs[0]);
    if (poly->power[2] == 5) { 
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
    double x2_min = x*x;
    double x2_max = rndu_multiply(x,x);
    double m1_min = x*poly->coeffs[1]; 
    double m1_max = rndu_multiply(x,poly->coeffs[1]); 
    double m2_min = x*poly->coeffs[3]; 
    double m2_max = rndu_multiply(x,poly->coeffs[3]); 
    double p1_min = m1_min+poly->coeffs[0];
    double p1_max = rndu_add(m1_max, poly->coeffs[0]);
    double p2_min = m2_min+poly->coeffs[2];
    double p2_max = rndu_add(m2_max, poly->coeffs[2]);
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
    if (poly->power[3] == 4) { 
      double p3_min_x_d = p3_min*x;
      double p3_max_x_d = p3_max*x;
      double m4_min = min(p3_min_x_d, p3_max_x_d);
      double p3_min_x_u = rndu_multiply(p3_min, x);
      double p3_max_x_u = rndu_multiply(p3_max, x);
      double m4_max = max(p3_min_x_u, p3_max_x_u);
      poly_lb = m4_min;
      poly_ub = m4_max;
    } else {
      poly_lb = p3_min;
      poly_ub = p3_max;
    }
    return true;
  } else if (poly->termsize == 5) {
    if (poly->power[4] == 5) {
      double x2_min = x*x;
      double x2_max = rndu_multiply(x, x);
      double m1_min = x*poly->coeffs[2];
      double m1_max = rndu_multiply(x, poly->coeffs[2]);
      double m2_min = x*poly->coeffs[4];
      double m2_max = rndu_multiply(x, poly->coeffs[4]);
      double p1_min = m1_min + poly->coeffs[1];
      double p1_max = rndu_add(m1_max, poly->coeffs[1]);
      double p2_min = m2_min + poly->coeffs[3];
      double p2_max = rndu_add(m2_max, poly->coeffs[3]);
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
      double m5_min = x*poly->coeffs[0];
      double m5_max = rndu_multiply(x, poly->coeffs[0]);
      double p4_min = m4_min+m5_min;
      double p4_max = rndu_add(m4_max, m5_max);
      poly_lb = p4_min;
      poly_ub = p4_max;
    } else {
      double x2_min = x*x;
      double x2_max = rndu_multiply(x,x);
      double m1_min = x*poly->coeffs[1];
      double m1_max = rndu_multiply(x,poly->coeffs[1]);
      double m2_min = x*poly->coeffs[3];
      double m2_max = rndu_multiply(x,poly->coeffs[3]);
      double c4_x2_min_d = x2_min*poly->coeffs[4];
      double c4_x2_max_d = x2_max*poly->coeffs[4];
      double m3_min = min(c4_x2_min_d, c4_x2_max_d);
      double c4_x2_min_u = rndu_multiply(x2_min, poly->coeffs[4]);
      double c4_x2_max_u = rndu_multiply(x2_max, poly->coeffs[4]);
      double m3_max = max(c4_x2_min_u, c4_x2_max_u);
      double p1_min = m1_min + poly->coeffs[0];
      double p1_max = rndu_add(m1_max, poly->coeffs[0]);
      double p2_min = m2_min + poly->coeffs[2];
      double p2_max = rndu_add(m2_max, poly->coeffs[2]);
      double p3_min = m3_min + p2_min;
      double p3_max = rndu_add(m3_max, p2_max);
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
      double p4_min = m4_min + p1_min;
      double p4_max = rndu_add(m4_max, p1_max);
      poly_lb = p4_min;
      poly_ub = p4_max;
    }
    return true;
  } else if (poly->termsize == 6) {
    if (poly->power[5] == 5) {
      double x2_min = x*x;
      double x2_max = rndu_multiply(x,x);
      double m1_min = poly->coeffs[1]*x;
      double m1_max = rndu_multiply(poly->coeffs[1], x);
      double p1_min = m1_min + poly->coeffs[0];
      double p1_max = rndu_add(m1_max, poly->coeffs[0]);
      double m2_min = poly->coeffs[3]*x;
      double m2_max = rndu_multiply(poly->coeffs[3], x);
      double p2_min = m2_min + poly->coeffs[2];
      double p2_max = rndu_add(m2_max, poly->coeffs[2]);
      double m3_min = poly->coeffs[5]*x;
      double m3_max = rndu_multiply(poly->coeffs[5], x);
      double p3_min = m3_min + poly->coeffs[4];
      double p3_max = rndu_add(m3_max, poly->coeffs[4]);
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
      double p4_min = m4_min+p2_min;
      double p4_max = rndu_add(m4_max, p2_max);
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
      double p5_min = m5_min+p1_min;
      double p5_max = m5_max+p1_max;
      poly_lb = p5_min;
      poly_ub = p5_max;
    } else {
      double x2_min = x*x;
      double x2_max = rndu_multiply(x, x);
      double x3_min = min(x2_min*x, x2_max*x);
      double x3_max = max(rndu_multiply(x2_min, x), rndu_multiply(x2_max, x));
      double m1_min = x*poly->coeffs[1];
      double m1_max = rndu_multiply(x, poly->coeffs[1]);
      double p1_min = m1_min+poly->coeffs[0];
      double p1_max = rndu_add(m1_max, poly->coeffs[0]);
      double c2_x2_min_d = x2_min*poly->coeffs[2];
      double c2_x2_max_d = x2_max*poly->coeffs[2];
      double m2_min = min(c2_x2_min_d, c2_x2_max_d);
      double c2_x2_min_u = rndu_multiply(x2_min, poly->coeffs[2]);
      double c2_x2_max_u = rndu_multiply(x2_max, poly->coeffs[2]);
      double m2_max = max(c2_x2_min_u, c2_x2_max_u);
      double p2_min = m2_min + p1_min;
      double p2_max = rndu_add(m2_max, p1_max);
      double m3_min = x*poly->coeffs[4];
      double m3_max = rndu_multiply(x, poly->coeffs[4]);
      double p3_min = m3_min+poly->coeffs[3];
      double p3_max = rndu_add(m3_max, poly->coeffs[3]);
      double c5_x2_min_d = x2_min*poly->coeffs[5];
      double c5_x2_max_d = x2_max*poly->coeffs[5];
      double m4_min = min(c5_x2_min_d, c5_x2_max_d);
      double c5_x2_min_u = rndu_multiply(x2_min, poly->coeffs[5]);
      double c5_x2_max_u = rndu_multiply(x2_max, poly->coeffs[5]);
      double m4_max = max(c5_x2_min_u, c5_x2_max_u);
      double p4_min = m4_min+p3_min;
      double p4_max = rndu_add(m4_max, p3_max);
      double p4_min_x3_min_d = p4_min*x3_min;
      double p4_min_x3_max_d = p4_min*x3_max;
      double p4_max_x3_min_d = p4_max*x3_min;
      double p4_max_x3_max_d = p4_max*x3_max;
      double m5_min = min(p4_min_x3_min_d, min(p4_min_x3_max_d, min(p4_max_x3_min_d, p4_max_x3_max_d)));
      double p4_min_x3_min_u = rndu_multiply(p4_min, x3_min);
      double p4_min_x3_max_u = rndu_multiply(p4_min, x3_max);
      double p4_max_x3_min_u = rndu_multiply(p4_max, x3_min);
      double p4_max_x3_max_u = rndu_multiply(p4_max, x3_max);
      double m5_max = max(p4_min_x3_min_u, max(p4_min_x3_max_u, max(p4_max_x3_min_u, p4_max_x3_max_u)));
      double p5_min = m5_min + p2_min;
      double p5_max = rndu_add(m5_max, p2_max);
      double m6_min = min(p5_min*x, p5_max*x);
      double m6_max = max(rndu_multiply(p5_min, x), rndu_multiply(p5_max, x));
      poly_lb = m6_min;
      poly_ub = m6_max;
    }
    return true;
  }
  return false;
}

bool PolyFinder::validate_and_fix_intervals(sample_data* sintervals, size_t ssize, polynomial* poly, int multi){
  bool return_val = true;
  if (multi) {
    for(size_t i = 0; i < ssize; i++){
      double y_lb, y_ub;
      bool check_poly = poly_evaluation_multi(sintervals[i].x, poly, y_lb, y_ub);
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
  } else {
    for(size_t i = 0; i < ssize; i++){
      double y = poly_evaluation(sintervals[i].x, poly);

      if(y < sintervals[i].orig_lb){
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
      else if(y > sintervals[i].orig_ub){
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
  }
  return return_val;
}

size_t PolyFinder::compute_violated_indices(size_t* violated_indices, interval_data* intervals, size_t nentries, polynomial* poly, int multi){
  size_t num_violated_indices = 0;
  if (multi) {
    for(size_t i = 0; i < nentries; i++){
      double y_lb, y_ub;
      poly_evaluation_multi(intervals[i].x, poly, y_lb, y_ub);
      if (y_lb < intervals[i].lb || y_lb > intervals[i].ub || y_ub < intervals[i].lb || y_ub > intervals[i].ub){
	violated_indices[num_violated_indices] = i;
	num_violated_indices++;
      }
    }
  } else {
    for(size_t i = 0; i < nentries; i++){
      double y = poly_evaluation(intervals[i].x, poly);
      if( y < intervals[i].lb || y > intervals[i].ub){
	violated_indices[num_violated_indices] = i;
	num_violated_indices++;
      }
    }
  }
  return num_violated_indices;
}

polynomial* PolyFinder::generate_polynomial(sample_data* sintervals, size_t ssize,
			  int* power, int power_size, int max_tries, int multi){

  for(int i = power_size - 1; i < power_size; i++){
    printf("Trying to generate a polynomial  with %d terms \n", i+1);

    int count = 0;
    while(count < max_tries){
      polynomial* p = solve_with_soplex(sintervals, ssize, power, i+1);
      if(p && validate_and_fix_intervals(sintervals, ssize, p, multi)){
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
