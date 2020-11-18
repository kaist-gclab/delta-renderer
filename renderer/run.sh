#!/usr/bin/env bash
./build.sh && \
GALLIUM_DRIVER=llvmpipe ./renderer 640 480 ../3d-model.stl ./output.bmp
