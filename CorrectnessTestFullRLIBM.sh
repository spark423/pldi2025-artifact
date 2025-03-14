#!/bin/bash

cd correctness-all
./CleanTest.sh
./BuildTest.sh
./RunParallelTestRLIBM.sh
