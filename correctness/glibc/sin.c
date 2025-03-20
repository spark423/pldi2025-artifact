#define __ELEM__ sin
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double sin");
    return 0;
}
