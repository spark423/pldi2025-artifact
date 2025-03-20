#define __ELEM__ rlibm_logf
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM logf without RNE");
    return 0;
}

