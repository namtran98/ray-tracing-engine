#!/bin/bash
clang++ -c -std=c++14 -stdlib=libc++ *.cpp */*.cpp
rm build*.o
mv *.o obj
clang++  -std=c++14 */*.o -o trace