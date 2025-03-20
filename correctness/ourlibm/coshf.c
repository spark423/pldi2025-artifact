#define __ELEM__ ourlibm_coshf
#define __MPFR_ELEM__ mpfr_cosh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds coshf");
    return 0;
}
