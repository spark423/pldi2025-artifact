#define __ELEM__ rlibm_sinpif
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x3c042416};
    RunTest("Original RLIBM sinpif with RNE", special_cases);
    return 0;
}
