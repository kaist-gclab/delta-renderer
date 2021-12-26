#!/usr/bin/env bash
docker run -it \
    -v $PWD:/delta \
    delta-renderer-base /bin/bash
