#!/usr/bin/env bash
g++ main.cpp -orenderer --std=c++17 \
$(pkg-config --cflags --libs gl) \
$(pkg-config --cflags --libs osmesa) \
$(pkg-config --cflags --libs glu)