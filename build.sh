#!/usr/bin/bash
clear

ISO_PATH="build/out/kernel.iso"
QEMU_COMMAND="qemu-system-x86_64 -cdrom $ISO_PATH -vga std -m 512M -serial mon:stdio"


if ! make clean; then
    echo -e "\n\e[31mTried to clean installation, but failed!\e[0m\n"
    exit 1
fi

if ! make -j"$(nproc)"; then
    echo -e "\n\e[31mBuild failed!\e[0m\n"
    exit 1
fi

# run
if ! $QEMU_COMMAND; then
    echo -e "\n\e[31mFailed to run QEMU!\e[0m\n"
    exit 1
fi
