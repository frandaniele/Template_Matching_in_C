#!/bin/bash

echo "procedural:"
time ./src/bin/procedural original.txt test.txt > proceduralresult.txt
gprof ./src/bin/procedural gmon.out > proceduralprof.txt

echo "parallel:"
time ./src/bin/paralela original.txt test.txt > parallelresult.txt
gprof ./src/bin/paralela gmon.out > paralelaprof.txt