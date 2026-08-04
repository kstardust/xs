#ifndef _LUA_EMBED_H
#define _LUA_EMBED_H

/* Execute an in-memory Lua chunk. Returns zero on success. */
int lua_run_string(const char *source);
int lua_run_cpu_test(void);

#endif
