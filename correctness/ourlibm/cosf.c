#define __ELEM__ ourlibm_cosf
#define __MPFR_ELEM__ mpfr_cos
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds cosf");
    return 0;
}
