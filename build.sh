#!/bin/bash
set -e
extraflag=
if [[ "$1" == "wasm64" ]]; then extraflag=-D__wasm64__; fi
clang `find ./src/ -name "*.c" -type f` -I./include -I./src/include -I./src/internal -I./arch/wasm -I./arch/generic -shared -std=c99 -nostdlib $extraflag -ffreestanding -fexcess-precision=standard -frounding-math -Wa,--noexecstack -ffunction-sections -fdata-sections -w -Wno-pointer-to-int-cast --target=$1 -o wclibc-$1.wasm
