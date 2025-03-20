#define __ELEM__ cospi
#define __MPFR_ELEM__ mpfr_cospi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double cospi");
    return 0;
}
