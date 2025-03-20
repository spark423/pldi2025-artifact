#define __ELEM__ rlibm_logf
#define __MPFR_ELEM__ mpfr_log
#include "LibTestHelperRNE.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM logf with RNE");
    return 0;
}

