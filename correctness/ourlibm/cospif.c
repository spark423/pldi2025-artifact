#define __ELEM__ ourlibm_cospif
#define __MPFR_ELEM__ mpfr_cospi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds cospif");
    return 0;
}
