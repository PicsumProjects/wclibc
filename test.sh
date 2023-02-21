target=$1
clang tests/*.c wclibc-${target}.wasm -I./include --target=$target -nostdlib -O3 -o wclibc-test-${target}.wasm
