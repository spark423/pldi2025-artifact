#!/bin/bash

cd correctness-all
./CleanTestRLIBM.sh
./BuildTestRLIBM.sh
./RunParallelTestRLIBM.sh
