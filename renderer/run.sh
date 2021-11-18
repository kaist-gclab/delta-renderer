#!/usr/bin/env bash
./build.sh

export GALLIUM_DRIVER=llvmpipe

SOURCE="../big.stl"

./renderer 800 800 0 < $SOURCE > ../0.bmp
./renderer 800 800 11.25 < $SOURCE > ../1.bmp
./renderer 800 800 22.5 < $SOURCE > ../2.bmp
./renderer 800 800 33.75 < $SOURCE > ../3.bmp
./renderer 800 800 45 < $SOURCE > ../4.bmp
./renderer 800 800 56.25 < $SOURCE > ../5.bmp
./renderer 800 800 67.5 < $SOURCE > ../6.bmp
./renderer 800 800 78.75 < $SOURCE > ../7.bmp
./renderer 800 800 90 < $SOURCE > ../8.bmp
./renderer 800 800 101.25 < $SOURCE > ../9.bmp
./renderer 800 800 112.5 < $SOURCE > ../10.bmp
./renderer 800 800 123.75 < $SOURCE > ../11.bmp
./renderer 800 800 135 < $SOURCE > ../12.bmp
./renderer 800 800 146.25 < $SOURCE > ../13.bmp
./renderer 800 800 157.5 < $SOURCE > ../14.bmp
./renderer 800 800 168.75 < $SOURCE > ../15.bmp
./renderer 800 800 180 < $SOURCE > ../16.bmp
./renderer 800 800 191.25 < $SOURCE > ../17.bmp
./renderer 800 800 202.5 < $SOURCE > ../18.bmp
./renderer 800 800 213.75 < $SOURCE > ../19.bmp
./renderer 800 800 225 < $SOURCE > ../20.bmp
./renderer 800 800 236.25 < $SOURCE > ../21.bmp
./renderer 800 800 247.5 < $SOURCE > ../22.bmp
./renderer 800 800 258.75 < $SOURCE > ../23.bmp
./renderer 800 800 270 < $SOURCE > ../24.bmp
./renderer 800 800 281.25 < $SOURCE > ../25.bmp
./renderer 800 800 292.5 < $SOURCE > ../26.bmp
./renderer 800 800 303.75 < $SOURCE > ../27.bmp
./renderer 800 800 315 < $SOURCE > ../28.bmp
./renderer 800 800 326.25 < $SOURCE > ../29.bmp
./renderer 800 800 337.5 < $SOURCE > ../30.bmp
./renderer 800 800 348.75 < $SOURCE > ../31.bmp
