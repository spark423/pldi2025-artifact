#define __ELEM__ rlibm_exp10f
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelperFP32.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Original RLIBM exp10f without RNE");
    return 0;
}
