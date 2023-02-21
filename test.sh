target=$1
clang tests/*.c wclibc-${target}.wasm -I./include -I./arch/wasm --target=$target -Wl,--no-entry -Wl,--export-all -nostdlib -O3 -o wclibc-test-${target}.wasm
