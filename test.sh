#!/bin/bash
if [ $1 = "S" ]
then
    ./get_img_pixels.sh img/original_20porciento.png img/test_20porciento.png
elif [ $1 = "M" ]
then
    ./get_img_pixels.sh img/original_50porciento.png img/test_50porciento.png
else
    ./get_img_pixels.sh img/DSC_2337_baw.png img/test.png
fi

TIMEFORMAT=%R

echo "procedural:"
time ./src/bin/procedural original.txt test.txt > proceduralresult.txt
gprof ./src/bin/procedural gmon.out > proceduralprof.txt

if [ $2 = "full" ]
then
    echo "parallel:"
    time ./src/bin/paralela original.txt test.txt > parallelresult.txt
    gprof ./src/bin/paralela gmon.out > paralelaprof.txt
fi