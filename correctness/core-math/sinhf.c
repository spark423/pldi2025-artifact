#define __ELEM__ cr_sinhf
#define __MPFR_ELEM__ mpfr_sinh
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH sinhf");
    return 0;
}
