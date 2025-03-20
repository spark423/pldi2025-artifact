#define __ELEM__ ourlibm_log10f_rz
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs log10f");
    return 0;
}
