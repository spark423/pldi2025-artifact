#define __ELEM__ rlibm_cosf
#define __MPFR_ELEM__ mpfr_cos
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x43a0bd2e, 0x513352f6, 0x55325019, 0x6f5d2d4c, 0xc3a0bd2e, 0xd13352f6, 0xd5325019, 0xef5d2d4c};
    RunTest("Original RLIBM cosf with RNE", special_cases);
    return 0;
}
