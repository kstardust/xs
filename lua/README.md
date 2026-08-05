# Embedded Lua runtime

This directory contains Lua 5.4.2 configured for the freestanding AArch64
kernel. Lua uses Picolibc for the C runtime and the allocator supplied by the
kernel embedding layer.

The build enables the Lua core, auxiliary library, base library, string
library, and math library. Filesystem-dependent loading and the `io`, `os`,
and `package` modules are not part of the kernel profile. Embedded scripts can
still be compiled from strings.

`LUA_FREESTANDING` and `LUA_NO_FILESYSTEM` select the kernel-specific profile.
`lstd.c` and `lstd.h` provide the small console and runtime adaptations needed
by that profile. `kernel/lua_embed.c` creates each Lua state, supplies its
allocator, and registers the supported built-in libraries.
