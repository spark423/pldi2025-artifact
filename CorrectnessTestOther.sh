#!/bin/bash

cd correctness
./CleanTest.sh
./BuildTest.sh
./RunParallelTestOther.sh
