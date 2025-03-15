#define __ELEM__ rlibm_sinhf
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelperSpecialCasesRNE.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x3a1285ff, 0x3b36aa1f, 0x3d09c4d8, 0x4288942b, 0xba1285ff, 0xbb36aa1f, 0xbd09c4d8, 0xbdf3ef37, 0xbf7df258, 0xc288942b};
    RunTest(argv[1], "Original RLIBM sinhf with RNE", special_cases);
    return 0;
}
