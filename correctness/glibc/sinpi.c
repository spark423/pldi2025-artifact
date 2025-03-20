#define __ELEM__ sinpi
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double sinpi");
    return 0;
}
