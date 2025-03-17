#define __ELEM__ rlibm_sinf
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x49e3aeb3, 0x66b014aa, 0xc9e3aeb3};
    RunTest(argv[1], "Original RLIBM sinf without RNE", special_cases);
    return 0;
}
