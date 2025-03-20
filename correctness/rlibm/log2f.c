#define __ELEM__ rlibm_log2f
#define __MPFR_ELEM__ mpfr_log2
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM log2f without RNE");
    return 0;
}

