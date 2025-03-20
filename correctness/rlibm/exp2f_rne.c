#define __ELEM__ rlibm_exp2f
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x3e0c0ac1, 0xbc3b04d4};
    RunTest("Original RLIBM exp2f with RNE", special_cases);
    return 0;
}
