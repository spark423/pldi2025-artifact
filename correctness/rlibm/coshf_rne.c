#define __ELEM__ rlibm_coshf
#define __MPFR_ELEM__ mpfr_cosh
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x3b43f588, 0x4288942b, 0xbb43f588, 0xc288942b};
    RunTest(argv[1], "Original RLIBM coshf without RNE", special_cases);
    return 0;
}
