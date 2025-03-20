#define __ELEM__ cr_logf
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH logf");
    return 0;
}
