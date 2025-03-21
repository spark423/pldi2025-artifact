#define __ELEM__ ourlibm_log2f_rz
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Rounding-invariant outputs log2f");
    return 0;
}
