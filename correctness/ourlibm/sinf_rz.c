#define __ELEM__ ourlibm_sinf_rz
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs sinf");
    return 0;
}
