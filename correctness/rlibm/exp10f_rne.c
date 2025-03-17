#define __ELEM__ rlibm_exp10f
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x3d781ef5, 0xba6597d7, 0xbd3a8dd9};
    RunTest(argv[1], "Original RLIBM exp10f without RNE", special_cases);
    return 0;
}
