#define __ELEM__ rlibm_logf
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x1b7679ff, 0x1e88452d, 0x3f2bf883, 0x3f800000, 0x3f83f1d0, 0x5cd69e88, 0x665e7ca6};
    RunTest("Original RLIBM logf with RNE", special_cases);
    return 0;
}

