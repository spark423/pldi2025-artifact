#define __ELEM__ log10
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x41200000, 0x42c80000, 0x447a0000, 0x461c4000, 0x47c35000, 0x49742400, 0x4b189680, 0x4cbebc20, 0x4e6e6b28, 0x501502f9};
    RunTest(argv[1], "glibc double log10", special_cases);
    return 0;
}
