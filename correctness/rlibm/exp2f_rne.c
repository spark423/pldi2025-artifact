#define __ELEM__ rlibm_exp2f
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelperRNE.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM exp2f with RNE");
    return 0;
}
