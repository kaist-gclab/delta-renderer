#!/usr/bin/env bash
g++ -g -Wall \
-O2 \
main.cpp \
bmp.cpp \
gmodel.cpp \
error.cpp \
grenderer.cpp \
util.cpp \
png.cpp \
-orenderer --std=c++17 \
$(pkg-config --cflags --libs gl) \
$(pkg-config --cflags --libs osmesa) \
-lpng