#!/bin/bash

cd correctness
./CleanTestOurLibm.sh
./BuildTestOurLibm.sh
./RunParallelTestOurLibm.sh
