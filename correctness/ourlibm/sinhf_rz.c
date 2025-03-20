#define __ELEM__ ourlibm_sinhf_rz
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs sinhf");
    return 0;
}
