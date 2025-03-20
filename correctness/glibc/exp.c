#define __ELEM__ exp
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelperSpecialCases.h"

int main(int argc, char** argv) {
    unsigned special_cases[] = {0xb4800001, 0xb5000002, 0xb5800004, 0xb5c00009, 0xb6000008, 0xb6400012, 0xb6800010};
    RunTest("glibc double exp", special_cases);
    return 0;
}
