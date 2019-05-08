#!/bin/bash
clang++ -g -c -std=c++14 -stdlib=libc++ *.cpp */*.cpp
rm build*.o
rm scene.ppm
mv *.o obj
clang++ -std=c++14 */*.o -o trace
./trace
open scene.ppm