#include "PolyGen.hpp"

#if defined(RNDZ)
const int rnd = FE_TOWARDZERO;
#elif defined(MULTI)
const int rnd = FE_DOWNWARD;
#else
const int rnd = FE_TONEAREST;
#endif

#ifdef MULTI
const int multi = 1;
#else
const int multi = 0;
#endif

#ifdef EXIT_ON_THRESHOLD
const int exit_on_threshold = 1;
#else
const int exit_on_threshold = 0;
#endif

void check_sorted(sample_info* sampled_indices, size_t ssize){
  double min= sampled_indices[0].key;

  for(size_t i = 0; i< ssize; i++){
    assert ( min <= sampled_indices[i].key);
    min = sampled_indices[i].key;
  }
  
}

int sample_compare(const void* s1, const void* s2){

  sample_info* e1 = (sample_info*) s1;
  sample_info* e2 = (sample_info*) s2;
  return e1->key > e2->key;
}

void print_sample(sample_info* sampled_indices, size_t size){

  double prev = 0.0;
  for(size_t i = 0; i < size; i++){
    assert(sampled_indices[i].key >= prev);
    prev = sampled_indices[i].key;
    printf("counter=%lu, key=%e, sample_index=%lu\n", i, sampled_indices[i].key,
	   sampled_indices[i].index);
  }
}

void weighted_random_sample(sample_info* sampled_indices, size_t ssize,
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
}

void evaluate_and_update_weights(size_t* violated_indices, size_t num_violated_indices,
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

void regenerate_random_values_and_reset_weights(interval_data* intervals,
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

void print_polyinfo(FILE* polynomial_file_fp, polynomial* p){
  if(p->termsize == 0){
    printf("Polynomial has no terms!\n");
    exit(0);
  }
  
  fprintf(polynomial_file_fp, "//Polynomial: y=%a x^(%d)",p->coeffs[0],p->power[0]);
  for(int j=1;j<p->termsize;j++){
    fprintf(polynomial_file_fp, " + %a x^(%d)",p->coeffs[j],p->power[j]);
  }
  fprintf(polynomial_file_fp, "\n");
}

int create_polynomial(FILE* interval_file_fp, FILE* polynomial_file_fp, vector<int> powers, int violate_threshold){
 
  assert(interval_file_fp != nullptr);
  assert(polynomial_file_fp != nullptr);

  /* count the number of entries */

  fseek(interval_file_fp, 0, SEEK_END);
  unsigned long nentries = ftell(interval_file_fp);
  nentries = nentries/(3*sizeof(double));
  printf("number of intervals = %lu\n", nentries);
  fseek(interval_file_fp, 0, SEEK_SET);
  fesetround(rnd);

  interval_data* intervals = (interval_data*) calloc(nentries, sizeof(interval_data));

  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  for (unsigned long i = 0; i < nentries; i++){
    double data_entry[3];
    size_t bytes = fread(data_entry, sizeof(double), 3, interval_file_fp);
    intervals[i].w = 1.0;
    intervals[i].u = distribution(generator);
    intervals[i].x = data_entry[0];
    intervals[i].lb = data_entry[1];
    intervals[i].ub = data_entry[2];
  }

  int powers_size = powers.size();

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
    
    weighted_random_sample(sampled_indices, cd, intervals, nentries);    
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
    PolyFinder poly_find;
    p = poly_find.generate_polynomial(sampled_intervals, samplesize, powers, powers_size, MAX_TRIES, multi);

    if(p){
      n_violated_indices = poly_find.compute_violated_indices(violated_indices, intervals, nentries, p, multi);
      printf("number of violated intervals: %lu, total iterations=%lu \n", n_violated_indices, total_iterations);

      if(n_violated_indices <= violate_threshold){
	if (n_violated_indices) fprintf(polynomial_file_fp, "Polynomial with violated inputs:\n");
	for(size_t m = 0; m < n_violated_indices; m++){		
	  if (m) fprintf(polynomial_file_fp, "else if (__builtin_expect(reduced_input == %a, 0)) y = %a;\n", intervals[violated_indices[m]].x, (intervals[violated_indices[m]].lb+intervals[violated_indices[m]].ub)/2);
	  else fprintf(polynomial_file_fp, "if (__builtin_expect(reduced_input == %a, 0)) y = %a;\n", intervals[violated_indices[m]].x, (intervals[violated_indices[m]].lb+intervals[violated_indices[m]].ub)/2);
	  if (m == n_violated_indices - 1) fprintf(polynomial_file_fp, "else {\n ");
	}
	print_polyinfo(polynomial_file_fp, p);
	if (n_violated_indices) fprintf(polynomial_file_fp, "\n}\n");
	if(exit_on_threshold){
	  break;
	}
      }
      
      evaluate_and_update_weights(violated_indices, n_violated_indices, intervals, nentries, powers_size);

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
      regenerate_random_values_and_reset_weights(intervals, nentries);
    }

    /* debugging feature to reset weights for the sample if not making progress*/
    if(n_violated_indices != 0 && (prev_violated_indices == n_violated_indices)){
      matched_violated_indices++;
      if(matched_violated_indices > SAMPLE_MATCH_THRESHOLD){
	matched_violated_indices = 0;
	n_violated_indices = 0;
	
	printf("not making progress, same number of violated indices, resetting weights, total_iterations=%lu\n", total_iterations);
	regenerate_random_values_and_reset_weights(intervals, nentries);
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
    printf("Polynomial has been written to the log file\n");
  }
  else {
    printf("Could not generate the polynomial that satisifies all intervals, check for partial results with a few violated intervals\n");
  }
  
  free(p);
  free(sampled_intervals);
  free(sampled_indices);
  free(intervals);
  free(violated_indices);
  
  return 0;

}
