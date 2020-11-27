#!/usr/bin/env bash
./build.sh && \
GALLIUM_DRIVER=swr ./renderer 640 480 < ../3d-model.stl > ./output.bmp
