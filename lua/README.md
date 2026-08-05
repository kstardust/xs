# Embedded Lua runtime

The official Lua 5.5.0 repository is pinned as the `src/` Git submodule.
`patch.sh` applies the embedded changes from `patch.diff` to that source tree,
and `Makefile` only handles compilation. Lua uses Picolibc for the C runtime
and the allocator supplied by the kernel embedding layer. See
`OFFICIAL_IMPORT.md` for provenance and update steps.

The build enables the Lua core, auxiliary library, base library, string
library, and math library. Filesystem-dependent loading and the `io`, `os`,
and `package` modules are not part of the kernel profile. Embedded scripts can
still be compiled from strings.

`LUA_FREESTANDING` and `LUA_NO_FILESYSTEM` select the kernel-specific profile.
Picolibc routes Lua's standard streams to the kernel UART.
`kernel/lua_embed.c` creates each Lua state, supplies its allocator, and
registers the supported built-in libraries.
