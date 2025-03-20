#define __ELEM__ cr_exp2f
#define __MPFR_ELEM__ mpfr_exp2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH exp2f");
    return 0;
}
