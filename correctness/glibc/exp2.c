#define __ELEM__ exp2
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    unsigned special_cases[] = {0x3b429d37, 0xbcf3a937};
    RunTest(argv[1], "glibc double exp2", special_cases);
    return 0;
}
