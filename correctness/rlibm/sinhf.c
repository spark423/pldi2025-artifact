#define __ELEM__ rlibm_sinhf
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM sinhf without RNE");
    return 0;
}
