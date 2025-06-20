#!/usr/bin/bash
clear

ISO_PATH="build/out/kernel.iso"

if ! make clean; then
    echo -e "\n\e[31mTried to clean installation, but failed!\e[0m\n"
    exit 1
fi

if ! make -j"$(nproc)"; then
    echo -e "\n\e[31mBuild failed!\e[0m\n"
    exit 1
fi

# run
qemu-system-i386 -cdrom "build/out/kernel.iso"