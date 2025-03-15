#define __ELEM__ rlibm_sinhf
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelperRNEFP32.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Original RLIBM sinhf with RNE");
    return 0;
}
