#define __ELEM__ rlibm_expf
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x41b7ee9a};
    RunTest(argv[1], "Original RLIBM expf with RNE", special_cases);
    return 0;
}
