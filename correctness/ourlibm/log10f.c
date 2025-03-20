#define __ELEM__ ourlibm_log10f
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds log10f");
    return 0;
}
