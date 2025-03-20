#define __ELEM__ rlibm_sinf
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x49e3aeb3, 0x66b014aa, 0xc9e3aeb3};
    RunTest("Original RLIBM sinf without RNE", special_cases);
    return 0;
}
