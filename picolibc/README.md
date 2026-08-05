# Embedded Picolibc runtime

The official Picolibc 1.8.12 repository is pinned as the `src/` Git
submodule. `Makefile` owns the freestanding AArch64 build and
`toolchain.cmake` contains the project configuration. Picolibc has no local
source patch.

Initialize the submodule with:

```sh
git submodule update --init --recursive
```
