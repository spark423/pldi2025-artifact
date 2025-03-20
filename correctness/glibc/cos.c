#define __ELEM__ cos
#define __MPFR_ELEM__ mpfr_cos
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double cos");
    return 0;
}
