#!/usr/bin/env bash
g++ \
    main.cpp \
    error.cpp \
    http.cpp \
    -oprocessor --std=c++17 \
    $(curl-config --cflags --libs)
