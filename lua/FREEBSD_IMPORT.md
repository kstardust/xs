# FreeBSD loader Lua import

The Lua core and libraries were imported from:

- FreeBSD source revision `5c4e8a6310973f22eb76835f1b0d5ba5dd9df2f7`
- `contrib/lua/src` (Lua 5.4.2)
- `stand/liblua/luaconf.h`

The embedded profile keeps FreeBSD's loader architecture but uses normal Lua
double-precision numbers. `LUA_NO_FILESYSTEM` removes `loadfile`, `dofile`,
and the auxiliary file APIs at compile time; `io`, `package`, and OS modules
are not compiled. String loading remains available for embedded scripts.

`lstd.c` and `lstd.h` retain the UART console adaptation of FreeBSD's loader
support routines. `lauxlib.c`, `lauxlib.h`, `lbaselib.c`, and `luaconf.h`
contain the small no-filesystem and numeric-hook changes described above.

`kernel/lua_embed.c` follows the state allocator callback and library
registration pattern from `stand/common/interp_lua.c`.
