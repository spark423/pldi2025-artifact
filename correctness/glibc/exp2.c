#define __ELEM__ exp2
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double exp2");
    return 0;
}
