#!/bin/bash
for filename in `find . | egrep '\.cpp'`; 
do 
  gcov-7 -n -o . $filename > /dev/null; 
done