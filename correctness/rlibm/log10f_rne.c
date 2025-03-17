#define __ELEM__ rlibm_log10f
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x8aea356, 0x23426d13, 0x3f7f1472, 0x3f7f7bf8, 0x4f134f83, 0x7956ba5e};
    RunTest(argv[1], "Original RLIBM log10f without RNE", special_cases);
    return 0;
}
