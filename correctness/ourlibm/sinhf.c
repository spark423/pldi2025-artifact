#define __ELEM__ ourlibm_sinhf
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds sinhf");
    return 0;
}
