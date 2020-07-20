#!/bin/bash
set -x
set -e

# Setup and build
mkdir -p ./linux_build
cd ./linux_build
cmake ..
make

# Execute tests. If they pass, run the simulation
./UnitTestRunner
if [ $? -eq 0 ]; then
    ./ConwaysLife
else
    echo "At least one test case failed. Please fix before running the simualtion"
fi