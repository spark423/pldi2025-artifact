#define __ELEM__ rlibm_expf
#define __MPFR_ELEM__ mpfr_exp
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM expf without RNE");
    return 0;
}
