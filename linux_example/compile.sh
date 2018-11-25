#!/bin/bash

echo "Compile script ...";

g++ -c main.cpp;
g++ -c test.cpp;
g++ -Wall -O2 -o main main.o test.o;

echo "Script complete ...";