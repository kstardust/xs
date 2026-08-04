#include <lua_embed.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static void *
loader_lua_realloc(void *context, void *pointer, size_t old_size,
    size_t new_size)
{
    (void)context;
    (void)old_size;
    if (new_size == 0) {
        free(pointer);
        return NULL;
    }
    return realloc(pointer, new_size);
}

/* Mirrors FreeBSD stand/common/interp_lua.c, minus libsa-backed modules. */
static const luaL_Reg loaded_libraries[] = {
    {"_G", luaopen_base},
    {LUA_STRLIBNAME, luaopen_string},
    {LUA_MATHLIBNAME, luaopen_math},
    {NULL, NULL}
};

int
lua_run_string(const char *source)
{
    lua_State *state;
    int status;

    const luaL_Reg *library;

    state = lua_newstate(loader_lua_realloc, NULL);
    if (state == NULL) {
        printf("lua: cannot allocate state\n");
        return LUA_ERRMEM;
    }
    for (library = loaded_libraries; library->func != NULL; library++) {
        luaL_requiref(state, library->name, library->func, 1);
        lua_pop(state, 1);
    }
    status = luaL_loadstring(state, source);
    if (status == LUA_OK)
        status = lua_pcall(state, 0, 0, 0);
    if (status != LUA_OK) {
        const char *message = lua_tostring(state, -1);
        printf("lua: %s\n", message != NULL ? message : "unknown error");
    }
    lua_close(state);
    return status;
}

static uint64_t
read_counter(void)
{
    uint64_t value;
    __asm__ volatile("isb; mrs %0, cntvct_el0" : "=r"(value));
    return value;
}

static uint64_t
read_counter_frequency(void)
{
    uint64_t value;
    __asm__ volatile("mrs %0, cntfrq_el0" : "=r"(value));
    return value;
}

int
lua_run_cpu_test(void)
{
    static const char source[] =
        "local limit = 100000\n"
        "local composite = {}\n"
        "local prime_count, prime_sum = 0, 0\n"
        "for candidate = 2, limit do\n"
        "  if not composite[candidate] then\n"
        "    prime_count = prime_count + 1\n"
        "    prime_sum = prime_sum + candidate\n"
        "    if candidate * candidate <= limit then\n"
        "      for multiple = candidate * candidate, limit, candidate do\n"
        "        composite[multiple] = true\n"
        "      end\n"
        "    end\n"
        "  end\n"
        "end\n"
        "assert(prime_count == 9592 and prime_sum == 454396537)\n"
        "local value, checksum = 0x12345678, 0\n"
        "for i = 1, 10000000 do\n"
        "  value = (1103515245 * value + 12345) & 0x7fffffff\n"
        "  checksum = (checksum + ((value ~ (value >> 7)) & 0xffff)) & 0x7fffffff\n"
        "end\n"
        "assert(value == 744751608 and checksum == 1265603629)\n"
        "assert(loadfile == nil and dofile == nil)\n"
        "assert(math.abs(-3.5) == 3.5 and math.sqrt(81) == 9)\n"
        "assert(math.abs(math.sin(math.pi / 6) - 0.5) < 1e-12)\n"
        "assert(math.abs(math.log(math.exp(2.5)) - 2.5) < 1e-12)\n"
        "local ok, message = pcall(function() error('expected test error') end)\n"
        "assert(not ok and type(message) == 'string')\n"
        "print('FreeBSD Lua CPU/math workload: passed', prime_count, checksum, math.sqrt(2))\n";
    uint64_t start = read_counter();
    int status = lua_run_string(source);
    uint64_t ticks = read_counter() - start;
    uint64_t frequency = read_counter_frequency();

    printf("Lua CPU time: %lu ms (%lu counter ticks)\n",
        ticks * 1000 / frequency, ticks);
    return status;
}
