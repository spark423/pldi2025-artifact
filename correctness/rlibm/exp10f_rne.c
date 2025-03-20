#define __ELEM__ rlibm_exp10f
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelperRNE.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM exp10f with RNE");
    return 0;
}
