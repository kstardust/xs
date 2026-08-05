Having fun with Armv8.

## Build

The C runtime is Picolibc 1.8.12, included as a Git submodule and configured
for single-threaded, freestanding AArch64. Initialize dependencies and build:

```sh
git submodule update --init --recursive
make
```

The build requires LLVM/Clang, LLD, CMake, and GNU Make. The board adapter in
`lib/platform.c` connects Picolibc to the PL011 UART, the kernel timer, and the
16 MiB heap declared in `link.ld`.
