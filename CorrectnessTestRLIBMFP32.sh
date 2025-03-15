#!/bin/bash

cd correctness
./CleanTestRLIBM.sh
./BuildTestRLIBM.sh
./RunParallelTestRLIBMFP32.sh
