#!/usr/bin/env bash
g++ -g \
main.cpp \
bmp.cpp \
loader.cpp \
error.cpp \
-orenderer --std=c++17 \
$(pkg-config --cflags --libs gl) \
$(pkg-config --cflags --libs osmesa) \
$(pkg-config --cflags --libs glu) \
$(pkg-config --cflags --libs glew)
