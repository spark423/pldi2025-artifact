#define __ELEM__ exp
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double exp");
    return 0;
}
