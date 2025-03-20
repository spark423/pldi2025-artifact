#define __ELEM__ exp10
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double exp10");
    return 0;
}
