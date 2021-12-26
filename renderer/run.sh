#!/usr/bin/env bash

export GALLIUM_DRIVER=llvmpipe

SOURCE="../assets/teapot.ascii.stl"

FILEEXT="png"

./renderer 800 800 0 <$SOURCE >../0.$FILEEXT &
./renderer 800 800 11.25 <$SOURCE >../1.$FILEEXT &
./renderer 800 800 22.5 <$SOURCE >../2.$FILEEXT &
./renderer 800 800 33.75 <$SOURCE >../3.$FILEEXT &
./renderer 800 800 45 <$SOURCE >../4.$FILEEXT &
./renderer 800 800 56.25 <$SOURCE >../5.$FILEEXT &
./renderer 800 800 67.5 <$SOURCE >../6.$FILEEXT &
./renderer 800 800 78.75 <$SOURCE >../7.$FILEEXT &
./renderer 800 800 90 <$SOURCE >../8.$FILEEXT &
./renderer 800 800 101.25 <$SOURCE >../9.$FILEEXT &
./renderer 800 800 112.5 <$SOURCE >../10.$FILEEXT &
./renderer 800 800 123.75 <$SOURCE >../11.$FILEEXT &
./renderer 800 800 135 <$SOURCE >../12.$FILEEXT &
./renderer 800 800 146.25 <$SOURCE >../13.$FILEEXT &
./renderer 800 800 157.5 <$SOURCE >../14.$FILEEXT &
./renderer 800 800 168.75 <$SOURCE >../15.$FILEEXT &
./renderer 800 800 180 <$SOURCE >../16.$FILEEXT &
./renderer 800 800 191.25 <$SOURCE >../17.$FILEEXT &
./renderer 800 800 202.5 <$SOURCE >../18.$FILEEXT &
./renderer 800 800 213.75 <$SOURCE >../19.$FILEEXT &
./renderer 800 800 225 <$SOURCE >../20.$FILEEXT &
./renderer 800 800 236.25 <$SOURCE >../21.$FILEEXT &
./renderer 800 800 247.5 <$SOURCE >../22.$FILEEXT &
./renderer 800 800 258.75 <$SOURCE >../23.$FILEEXT &
./renderer 800 800 270 <$SOURCE >../24.$FILEEXT &
./renderer 800 800 281.25 <$SOURCE >../25.$FILEEXT &
./renderer 800 800 292.5 <$SOURCE >../26.$FILEEXT &
./renderer 800 800 303.75 <$SOURCE >../27.$FILEEXT &
./renderer 800 800 315 <$SOURCE >../28.$FILEEXT &
./renderer 800 800 326.25 <$SOURCE >../29.$FILEEXT &
./renderer 800 800 337.5 <$SOURCE >../30.$FILEEXT &
./renderer 800 800 348.75 <$SOURCE >../31.$FILEEXT &
wait
