#define __ELEM__ ourlibm_expf_rz
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs expf");
    return 0;
}
