#define __ELEM__ ourlibm_expf
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds expf");
    return 0;
}
