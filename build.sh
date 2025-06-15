#!/usr/bin/bash
clear
make clean
make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed!!!!!!!!!!!!!"
    exit 1
fi