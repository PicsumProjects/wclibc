set -e
build_file() {
of=$RANDOM.ll
clang $2 -I./include -std=c99 -nostdinc -ffreestanding -fexcess-precision=standard -frounding-math -Wa,--noexecstack -ffunction-sections -fdata-sections -w -Wno-pointer-to-int-cast --target=$1 -emit-llvm -c -S -o $of
llc -march=$2 -filetype=obj $of -o ${of}.o
echo ${of}.o
}

buildlist=

for buildfile in ./src/*.c
do
    output=$(build_file $buildfile $1)
    buildlist=$buildlist $output
done

wasm-ld --no-entry $buildlist -o wclibc.wasm --strip-all --export-dynamic --import-memory

