target=$1
clang tests/*.c wclibc-${target}.wasm --target=$target -nostdlib -O3 -o wclibc-test-${target}.wasm
