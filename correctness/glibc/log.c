#define __ELEM__ log
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0x3c413d3a, 0x41178feb, 0x4c5d65a5, 0x65d890d3, 0x6f31a8ec};
    RunTest("glibc double log", special_cases);
    return 0;
}
