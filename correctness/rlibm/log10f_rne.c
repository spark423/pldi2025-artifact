#define __ELEM__ rlibm_log10f
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x8aea356, 0x23426d13, 0x3f7f1472, 0x3f7f7bf8, 0x4f134f83, 0x7956ba5e};
    RunTest("Original RLIBM log10f with RNE", special_cases);
    return 0;
}
