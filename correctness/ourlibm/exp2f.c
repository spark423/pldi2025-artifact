#define __ELEM__ ourlibm_exp2f
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds exp2f");
    return 0;
}
