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

echo -e "\033[1m* Checking correctness of OurLibm, RLIBM, CORE-MATH, and glibc's implementations of all functions for various FP representations\033[0m"
echo -e "\033[1m* This will take a long time\033[0m"
echo -e "\033[1m* When each function is completely tested, it will print the result\033[0m"
echo -e "\033[1m* In the mean time, you can check the progress in Result/allrep/<function name>.txt\033[0m"
echo -e "\033[1m\tRunning testing script in parallel\033[0m"
echo -e "\033[1m\tParallelism: $parallelism jobs\033[0m"
echo -e "\033[1m\tEstimated time: > 24 hours \033[0m"
cat ParallelCommand.txt | parallel -j $parallelism
