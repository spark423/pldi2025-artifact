#define __ELEM__ rlibm_log2f
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x3f800000};
    RunTest("Original RLIBM logf without RNE", special_cases);
    return 0;
}

