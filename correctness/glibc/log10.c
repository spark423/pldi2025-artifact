#define __ELEM__ log10
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double log10");
    return 0;
}
