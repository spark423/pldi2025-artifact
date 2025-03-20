#define __ELEM__ ourlibm_log2f
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Rounding-invariant input bounds log2f");
    return 0;
}
