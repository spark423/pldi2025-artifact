#include "polynomial-gen/PolyGenFromFile.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Usage : %s <interval file> <log file><violate threshold>\n", argv[0]);
    printf("Input : <interval file> - file containing reduced constrains\n");
    printf("Output: <log file> - where we print the polynomial\n");
    printf("Parameter: <violate threshold> - the number of allowed violated inputs in the final polynomial\n");
    exit(0);
  }
  std::vector<int> powers({0,2,4});
  FILE* interval_file = fopen(argv[1], "r");
  FILE* polynomial_file = fopen(argv[2], "w");
  char* str_ptr;
  int violate_threshold = strtol(argv[3], &str_ptr, 10);
  if ((errno == ERANGE)&&(str_ptr == argv[3])) {
    printf("Invalid parameter for violated threshold (must be a valid integer)\n");
    exit(0);
  } 
  create_polynomial(interval_file, polynomial_file,  powers, violate_threshold);  
  fclose(interval_file);
  fclose(polynomial_file);
  return 0;
}
