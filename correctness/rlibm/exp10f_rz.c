#define __ELEM__ rlibm_exp10f_rz
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Rounding-invariant outputs exp10f");
    return 0;
}
