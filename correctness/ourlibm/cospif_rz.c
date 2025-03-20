#define __ELEM__ ourlibm_cospif_rz
#define __MPFR_ELEM__ mpfr_cospi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant outputs cospif");
    return 0;
}
