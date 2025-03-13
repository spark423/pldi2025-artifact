#!/bin/bash

cd correctness
./CleanTest.sh
./BuildTest.sh
./RunParallelTestOurLibm.sh
