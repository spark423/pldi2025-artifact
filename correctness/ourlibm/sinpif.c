#define __ELEM__ ourlibm_sinpif
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Rounding-invariant input bounds sinpif");
    return 0;
}
