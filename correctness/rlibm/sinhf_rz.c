#define __ELEM__ rlibm_sinhf_rz
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Rounding-invariant outputs sinhf");
    return 0;
}
