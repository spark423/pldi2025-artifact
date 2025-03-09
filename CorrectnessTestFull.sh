#!/bin/bash

cd correctness_all
sh CleanTest.sh
sh BuildTest.sh
sh RunParallelTest.sh
