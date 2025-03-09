#!/bin/bash

cd correctness
sh CleanTest.sh
sh BuildTest.sh
sh RunParallelTest.sh
