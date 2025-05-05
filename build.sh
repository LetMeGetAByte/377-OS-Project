#!/bin/bash
shopt -s expand_aliases
source .source

# Configuration
OS_NAME=os
SRC_DIR=src
BUILD_DIR=build
ISO_DIR=isodir
BOOT_DIR=$ISO_DIR/boot
GRUB_DIR=$BOOT_DIR/grub

mkdir -p $BUILD_DIR

echo "[1] Assembling boot.s..."
as --32 $SRC_DIR/boot.s -o $BUILD_DIR/boot.o

echo "[2] Compiling kernel.c..."
gcc -c $SRC_DIR/kernel.c -o $BUILD_DIR/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Isrc

echo "[3] Compiling drivers..."
DRIVER_OBJECTS=""
for file in $(find $SRC_DIR/drivers -name "*.c"); do
    objfile="$BUILD_DIR/$(basename "$file" .c).o"
    gcc -c "$file" -o "$objfile" -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Isrc
    if [ ! -f "$objfile" ]; then
        echo "❌ Failed to compile driver: $file"
        exit 1
    fi
    DRIVER_OBJECTS="$DRIVER_OBJECTS $objfile"
done

echo "[4] Linking kernel and drivers..."
gcc -T $SRC_DIR/linker.ld -o $BUILD_DIR/$OS_NAME.bin -ffreestanding -O2 -nostdlib $BUILD_DIR/boot.o $BUILD_DIR/kernel.o $DRIVER_OBJECTS -lgcc

echo "[5] Performing sanity checks..."
for file in $BUILD_DIR/boot.o $BUILD_DIR/kernel.o $DRIVER_OBJECTS; do
    if [ ! -f "$file" ]; then
        echo "❌ Error: Missing object file $file"
        exit 1
    fi
done

if [ ! -f $BUILD_DIR/$OS_NAME.bin ]; then
    echo "❌ Error: Kernel binary not found!"
    exit 1
fi

echo "[6] Creating ISO image..."
mkdir -p $GRUB_DIR
cp $BUILD_DIR/$OS_NAME.bin $BOOT_DIR/$OS_NAME.bin
cp grub.cfg $GRUB_DIR/grub.cfg
grub-mkrescue -o $OS_NAME.iso $ISO_DIR

if [ ! -f $OS_NAME.iso ]; then
    echo "❌ Error: ISO image not found!"
    exit 1
fi

echo "[7] Performing cleanup..."
rm -fr $ISO_DIR
rm -fr $BUILD_DIR

echo "✅ Done! Bootable ISO is $OS_NAME.iso"
