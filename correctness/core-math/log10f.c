#define __ELEM__ cr_log10f
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH log10f");
    return 0;
}
