#define __ELEM__ rlibm_log2f
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Original RLIBM log2f without RNE");
    return 0;
}
