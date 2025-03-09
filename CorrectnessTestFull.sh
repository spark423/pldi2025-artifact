#!/bin/bash

cd correctness_all
./CleanTest.sh
./BuildTest.sh
./RunParallelTest.sh
