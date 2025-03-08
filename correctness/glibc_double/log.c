#define __ELEM__ log
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "glibc double log");
    return 0;
}
