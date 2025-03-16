#pragma once
#define SOPLEX_WITH_GMP
#pragma STDC FENV_ACCESS ON
#include <fenv.h>
#include <fstream>
#include <math.h>
#include <memory>
#include <random>
#include <soplex.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TRIES 200
#define SAMPLE_MATCH_THRESHOLD 20
#define MAX_ITERATIONS 1200

using namespace soplex;
using namespace std;

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
  vector<int> power;
  double* coeffs;
} polynomial;

typedef union {
  double d;
  uint64_t x;
} double_x;

class PolyFinder { 
    public :
    polynomial* solve_with_soplex(sample_data* sintervals, size_t ssize, vector<int> power, int termsize);
    double poly_horner_evaluation(double x, polynomial* poly);
    double poly_evaluation(double x, polynomial* poly);
    bool poly_evaluation_multi(double x, polynomial* poly, double& poly_lb, double& poly_ub);
    bool validate_and_fix_intervals(sample_data* sintervals, size_t ssize, polynomial* poly, int multi);
    size_t compute_violated_indices(size_t* violated_indices, interval_data* intervals, size_t nentries, polynomial* poly, int multi);
    polynomial* generate_polynomial(sample_data* sintervals, size_t ssize, vector<int> power, int power_size, int max_tries, int multi);    
};
