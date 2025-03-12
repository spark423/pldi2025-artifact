#define __ELEM__ rlibm_cosf
#define __MPFR_ELEM__ mpfr_cos
#include "LibTestHelperRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "Original RLIBM cosf under RNE");
    return 0;
}
