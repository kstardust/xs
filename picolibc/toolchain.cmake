set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_ASM_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_AR /opt/homebrew/opt/llvm/bin/llvm-ar)
set(CMAKE_RANLIB /opt/homebrew/opt/llvm/bin/llvm-ranlib)

set(TARGET_COMPILE_OPTIONS
    --target=aarch64-elf
    -ffreestanding
    -fno-builtin
    -nostdlib)

set(__SINGLE_THREAD ON CACHE BOOL "Disable multithreading support")
set(__THREAD_LOCAL_STORAGE OFF CACHE BOOL "Disable TLS until the kernel supports threads")
set(__THREAD_LOCAL_STORAGE_API OFF CACHE BOOL "Disable TLS helper APIs")
set(__GLOBAL_ERRNO ON CACHE BOOL "Use a global errno in the single-threaded runtime")
set(__ATOMIC_UNGETC 0 CACHE BOOL "No atomic stdio operations are needed")
set(ENABLE_MALLOC ON CACHE BOOL "Build the Picolibc allocator")
set(TESTS OFF CACHE BOOL "Do not build the upstream test executables")
