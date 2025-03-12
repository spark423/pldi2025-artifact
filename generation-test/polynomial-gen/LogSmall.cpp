#include "polynomial-gen/PolyGenFromFile.h"

int main(int argc, char** argv) {
  /*
  if (argc != 4 && argc != 5) {
      printf("Usage : %s <interval file> <log file> <header file>\n", argv[0]);
      printf("Input : <interval file> - file containing reduced constrains\n");
      printf("Output: <log file> - where we print some logging information\n");
      printf("Output: <header file> - the file containing coefficients\n");
  }
  */
  std::vector<int> powers({1, 2, 3, 4});

  FILE* interval_file = fopen(argv[1], "r");
  create_polynomial(interval_file, powers);  
  fclose(interval_file);
  return 0;
}
