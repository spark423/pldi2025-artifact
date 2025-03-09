#define __ELEM__ rlibm_sinf
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Original RLIBM sinf");
    return 0;
}
