#!/usr/bin/bash
clear

ISO_PATH="/home/russian95/Inicium/build/out/kernel.iso"
WIN_DESKTOP="/mnt/c/Users/russian95/Desktop"

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
powershell.exe -Command "& 'C:\\Program Files\\qemu\\qemu-system-i386.exe' -cdrom 'C:\\Users\\russian95\\Desktop\\kernel.iso'"
