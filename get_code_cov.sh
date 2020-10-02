#!/bin/bash

# for each cpp file..
for filename in `find . | egrep '\.cpp'`; 
do 
  # run gcov to check how many lines have been executed
  gcov-5 -n -o . $filename > /dev/null;
done