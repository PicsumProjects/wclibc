set -e
clang ./src/*.c -I./include -shared -std=c99 -nostdinc -ffreestanding -fexcess-precision=standard -frounding-math -Wa,--noexecstack -ffunction-sections -fdata-sections -w -Wno-pointer-to-int-cast --target=$1 -o wclibc-$1.wasm
