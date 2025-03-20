#define __ELEM__ ourlibm_coshf_rz
#define __MPFR_ELEM__ mpfr_cosh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs coshf");
    return 0;
}
