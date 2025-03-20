#define __ELEM__ cr_exp10f
#define __MPFR_ELEM__ mpfr_exp10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH exp10f");
    return 0;
}
