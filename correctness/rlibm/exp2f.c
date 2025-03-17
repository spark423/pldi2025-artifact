#define __ELEM__ rlibm_exp2f
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x3e0c0ac1, 0xbc3b04d4};
    RunTest(argv[1], "Original RLIBM exp2f with RNE", special_cases);
    return 0;
}
