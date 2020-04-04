#!/bin/bash -xe
cd ..
cppcheck -v --library=qt --xml --enable=all --quiet --std=c++11 --suppress=purgedConfiguration -I src/app -I src/common 2>cppcheck.xml
tools/cppcheck-htmlreport --file=cppcheck.xml --report-dir=cppcheck-html
rm cppcheck.xml
nohup x-www-browser cppcheck-html/index.html &
