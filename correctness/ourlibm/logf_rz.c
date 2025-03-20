#define __ELEM__ ourlibm_logf_rz
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs logf");
    return 0;
}
