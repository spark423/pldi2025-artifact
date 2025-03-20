#define __ELEM__ log2
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double log2");
    return 0;
}
