#define __ELEM__ rlibm_expf
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x41b7ee9a};
    RunTest("Original RLIBM expf with RNE", special_cases);
    return 0;
}
