#!/bin/bash

parallelism=12

while getopts j: flag
do
    case "${flag}" in
        j) parArg=${OPTARG};;
    esac
done

if [ "$parArg" -eq "$parArg" ] 2>/dev/null
then
   parallelism=$parArg
fi

echo "\033[1m* Checking correctness of RLIBM's implementations of all functions for various FP representations\033[0m"
echo "\033[1m* When each function is completely tested, it will print the result\033[0m"
echo "\033[1m\tRunning testing script in parallel\033[0m"
echo "\033[1m\tParallelism: $parallelism jobs\033[0m"
cat ParallelCommandRLIBM.txt | parallel -j $parallelism
