#define __ELEM__ ourlibm_sinpif
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds sinpif");
    return 0;
}
