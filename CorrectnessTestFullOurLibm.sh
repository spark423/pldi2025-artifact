#!/bin/bash

cd correctness-all
./CleanTest.sh
./BuildTest.sh
./RunParallelTestOurLibm.sh
