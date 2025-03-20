#define __ELEM__ rlibm_log10f
#define __MPFR_ELEM__ mpfr_log10
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM log10f without RNE");
    return 0;
}
