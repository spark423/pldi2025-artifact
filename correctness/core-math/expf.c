#define __ELEM__ cr_expf
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "CORE-MATH expf");
    return 0;
}
