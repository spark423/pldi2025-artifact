#define __ELEM__ ourlibm_exp10f_rz
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs exp10f");
    return 0;
}
