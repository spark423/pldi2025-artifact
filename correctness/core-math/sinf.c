#define __ELEM__ cr_sinf
#define __MPFR_ELEM__ mpfr_sin
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH sinf");
    return 0;
}
