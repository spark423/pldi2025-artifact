#define __ELEM__ rlibm_sinpif
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {};
    RunTest(argv[1], "Original RLIBM sinpif with RNE", special_cases);
    return 0;
}
