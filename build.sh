#!/bin/bash
shopt -s expand_aliases
source .source

# Configuration
ISO_DIR=isodir
BOOT_DIR=$ISO_DIR/boot
GRUB_DIR=$BOOT_DIR/grub

echo "[1] Assembling boot.s..."
as --32 ./src/boot.s -o ./build/boot.o

echo "[2] Compiling kernel.c..."
gcc -c ./src/kernel.c -o ./build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

echo "[3] Linking kernel..."
gcc -T ./src/linker.ld -o ./build/os.bin -ffreestanding -O2 -nostdlib ./build/boot.o ./build/kernel.o -lgcc

echo "[4] Creating ISO image..."
mkdir -p $GRUB_DIR
cp ./build/os.bin $BOOT_DIR/os.bin
cp grub.cfg $GRUB_DIR/grub.cfg
grub-mkrescue -o os.iso $ISO_DIR
rm -fr $ISO_DIR

echo "✅ Done! Bootable ISO is os.iso"
