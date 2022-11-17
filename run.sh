#!/usr/bin/env bash
docker run -it --rm \
    -v $PWD:/delta \
    delta-renderer-base /bin/bash
