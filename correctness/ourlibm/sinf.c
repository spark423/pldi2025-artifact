#define __ELEM__ ourlibm_sinf
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds sinf");
    return 0;
}
