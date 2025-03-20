#define __ELEM__ rlibm_sinpif
#define __MPFR_ELEM__ mpfr_sinpi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM sinpif without RNE");
    return 0;
}
