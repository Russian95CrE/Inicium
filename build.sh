#!/usr/bin/bash
clear

ISO_PATH="build/out/kernel.iso"

make clean
make -j$(nproc)
if [ $? -ne 0 ]; then
    echo "Build failed!!!!!!!!!!!!"
    exit 1
fi

# copy
cp "$ISO_PATH" "$WIN_DESKTOP/kernel.iso"

sleep 1

# run
qemu-system-i386 -cdrom "build/out/kernel.iso"
