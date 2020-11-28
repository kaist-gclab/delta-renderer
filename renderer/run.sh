#!/usr/bin/env bash
./build.sh

export GALLIUM_DRIVER=llvmpipe

./renderer 800 800 0 < ../assets/teapot.ascii.stl > ../0.bmp
./renderer 800 800 11.25 < ../assets/teapot.ascii.stl > ../1.bmp
./renderer 800 800 22.5 < ../assets/teapot.ascii.stl > ../2.bmp
./renderer 800 800 33.75 < ../assets/teapot.ascii.stl > ../3.bmp
./renderer 800 800 45 < ../assets/teapot.ascii.stl > ../4.bmp
./renderer 800 800 56.25 < ../assets/teapot.ascii.stl > ../5.bmp
./renderer 800 800 67.5 < ../assets/teapot.ascii.stl > ../6.bmp
./renderer 800 800 78.75 < ../assets/teapot.ascii.stl > ../7.bmp
./renderer 800 800 90 < ../assets/teapot.ascii.stl > ../8.bmp
./renderer 800 800 101.25 < ../assets/teapot.ascii.stl > ../9.bmp
./renderer 800 800 112.5 < ../assets/teapot.ascii.stl > ../10.bmp
./renderer 800 800 123.75 < ../assets/teapot.ascii.stl > ../11.bmp
./renderer 800 800 135 < ../assets/teapot.ascii.stl > ../12.bmp
./renderer 800 800 146.25 < ../assets/teapot.ascii.stl > ../13.bmp
./renderer 800 800 157.5 < ../assets/teapot.ascii.stl > ../14.bmp
./renderer 800 800 168.75 < ../assets/teapot.ascii.stl > ../15.bmp
./renderer 800 800 180 < ../assets/teapot.ascii.stl > ../16.bmp
./renderer 800 800 191.25 < ../assets/teapot.ascii.stl > ../17.bmp
./renderer 800 800 202.5 < ../assets/teapot.ascii.stl > ../18.bmp
./renderer 800 800 213.75 < ../assets/teapot.ascii.stl > ../19.bmp
./renderer 800 800 225 < ../assets/teapot.ascii.stl > ../20.bmp
./renderer 800 800 236.25 < ../assets/teapot.ascii.stl > ../21.bmp
./renderer 800 800 247.5 < ../assets/teapot.ascii.stl > ../22.bmp
./renderer 800 800 258.75 < ../assets/teapot.ascii.stl > ../23.bmp
./renderer 800 800 270 < ../assets/teapot.ascii.stl > ../24.bmp
./renderer 800 800 281.25 < ../assets/teapot.ascii.stl > ../25.bmp
./renderer 800 800 292.5 < ../assets/teapot.ascii.stl > ../26.bmp
./renderer 800 800 303.75 < ../assets/teapot.ascii.stl > ../27.bmp
./renderer 800 800 315 < ../assets/teapot.ascii.stl > ../28.bmp
./renderer 800 800 326.25 < ../assets/teapot.ascii.stl > ../29.bmp
./renderer 800 800 337.5 < ../assets/teapot.ascii.stl > ../30.bmp
./renderer 800 800 348.75 < ../assets/teapot.ascii.stl > ../31.bmp
