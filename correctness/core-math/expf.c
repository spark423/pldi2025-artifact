#define __ELEM__ cr_expf
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH expf");
    return 0;
}
