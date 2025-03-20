#define __ELEM__ cr_cosf
#define __MPFR_ELEM__ mpfr_cos
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH cosf");
    return 0;
}
