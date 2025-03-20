#define __ELEM__ ourlibm_exp10f
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds exp10f");
    return 0;
}
