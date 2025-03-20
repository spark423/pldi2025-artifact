#define __ELEM__ ourlibm_sinpif_rz
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs sinpif");
    return 0;
}
