#define __ELEM__ cosh
#define __MPFR_ELEM__ mpfr_cosh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double cosh");
    return 0;
}
