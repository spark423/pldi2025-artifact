#include <iostream>

#include "libm.h"

using namespace::std;

typedef struct {
  double x;
  double lb;
  double ub;
  unsigned long idx;
} interval_data;

int main(int argc, char** argv){

  FILE* fp_src = fopen(argv[1], "r");
  fseek(fp_src, 0, SEEK_END);
  unsigned long nentries = ftell(fp_src);
  nentries = nentries/(3*sizeof(double));
  printf("number of intervals = %lu\n", nentries);
  fseek(fp_src, 0, SEEK_SET);

  FILE* fp_dest1 = fopen(argv[2], "w");
  FILE* fp_dest2 = fopen(argv[3], "w");
  double split_point = std::stod(argv[4]);

  interval_data* intervals = (interval_data*) calloc(nentries, sizeof(interval_data)); 
  unsigned long mid = nentries/2;
  double data_entry[3];
  for (unsigned long i = 0; i < nentries; i++){
    size_t bytes = fread(data_entry, sizeof(double), 3, fp_src);
    if (data_entry[0] < split_point) {
      fwrite(data_entry, sizeof(double), 3, fp_dest1);
    } else {
      fwrite(data_entry, sizeof(double), 3, fp_dest2);
    }
  }

  fclose(fp_src);
  fclose(fp_dest1);
  fclose(fp_dest2);
  return 0;
}
