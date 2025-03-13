#!/bin/bash

cd correctness
./CleanTest.sh
./BuildTest.sh
./RunParallelTestRLIBM.sh
