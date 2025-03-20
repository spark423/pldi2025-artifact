#define __ELEM__ rlibm_cospif
#define __MPFR_ELEM__ mpfr_cospi
#include "LibTestHelper.h"

int main(int argc, char** argv) {
    RunTest("Original RLIBM cospif without RNE");
    return 0;
}
