#define __ELEM__ cr_logf
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "CORE-MATH logf");
    return 0;
}
