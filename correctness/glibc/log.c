#define __ELEM__ log
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double log");
    return 0;
}
