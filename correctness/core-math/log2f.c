#define __ELEM__ cr_log2f
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("CORE-MATH log2f");
    return 0;
}
