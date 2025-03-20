#define __ELEM__ rlibm_exp10f
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x3d781ef5, 0xba6597d7, 0xbd3a8dd9};
    RunTest("Original RLIBM exp10f without RNE", special_cases);
    return 0;
}
