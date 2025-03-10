#define __ELEM__ cospi
#define __MPFR_ELEM__ mpfr_cospi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <log file>\n", argv[0]);
        exit(0);
    }
    RunTest(argv[1], "glibc double cospi");
    return 0;
}
