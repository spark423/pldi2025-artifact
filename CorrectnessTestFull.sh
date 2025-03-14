#!/bin/bash

cd correctness-all
./CleanTest.sh
./BuildTest.sh
./RunParallelTest.sh
