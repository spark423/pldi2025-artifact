#!/bin/bash

cd correctness_all
./CleanTest.sh
./BuildTest.sh
./RunParallelTestOurLibm.sh
