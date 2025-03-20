#define __ELEM__ sinh
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("glibc double sinh");
    return 0;
}
