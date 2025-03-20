#define __ELEM__ rlibm_sinhf
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelperRNE.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM sinhf with RNE");
    return 0;
}
