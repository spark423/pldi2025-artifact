#define __ELEM__ ourlibm_logf
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds logf");
    return 0;
}
