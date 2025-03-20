#define __ELEM__ rlibm_coshf
#define __MPFR_ELEM__ mpfr_cosh
#include "LibTestHelperRNE.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM coshf with RNE");
    return 0;
}
