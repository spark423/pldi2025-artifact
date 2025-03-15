#!/bin/bash

cd correctness-all
./CleanTestOurLibm.sh
./BuildTestOurLibm.sh
./RunParallelTestOurLibm.sh
