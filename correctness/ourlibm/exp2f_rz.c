#define __ELEM__ ourlibm_exp2f_rz
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs exp2f");
    return 0;
}
