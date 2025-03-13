#define __ELEM__ rlibm_exp2f
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelperFP32.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Original RLIBM exp2f");
    return 0;
}
