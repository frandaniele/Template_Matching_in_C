#!/bin/bash
if [ $1 = "S" ]
then
    ./get_img_pixels.sh img/original_20porciento.png img/test_20porciento.png $3
elif [ $1 = "M" ]
then
    ./get_img_pixels.sh img/original_50porciento.png img/test_50porciento.png $3
elif [ $1 = "L" ]
then
    ./get_img_pixels.sh img/DSC_2337_baw.png img/test.png $3
fi

TIMEFORMAT=%R
if [ $2 = "S" ]
then
    echo "procedural:"
    time ./src/bin/procedural original.txt test.txt > proceduralresult.txt
elif [ $2 = "P" ]
then
    echo "parallel:"
    time ./src/bin/paralela original.txt test.txt > parallelresult.txt
else
    sleep 1
    echo "procedural:"
    time ./src/bin/procedural original.txt test.txt > proceduralresult.txt
    
    sleep 1
    echo "parallel:"
    time ./src/bin/paralela original.txt test.txt > parallelresult.txt
fi