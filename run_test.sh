#!/bin/sh


echo "### run \"./test\" from . directory. ####"
./test
echo

echo "### run \"./test_wrapper\" from . directory. ####"
./test_wrapper
echo

if [ ! -d ./run_test_dir ]; then
    mkdir ./run_test_dir
    if [ $? -ne 0 ]; then
        echo "Error: \"mkdir ./run_test_dir\". Exit."
        exit 1
    fi;
fi;

echo "### \"cd ./run_test_dir\" ###"
cd ./run_test_dir
echo

echo "### run \"../test\" from ./run_test_dir directory. ####"
../test
echo

echo "### run \"../test_wrapper\" from ./run_test_dir directory. ####"
../test_wrapper
echo
