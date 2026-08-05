# Official Lua import

The `src/` Git submodule points to the Lua team's official repository at tag
`v5.5.0`, commit `a5522f06d2679b8f18534fd6a9968f7eb539dc31`.

Repository: <https://github.com/lua/lua>

Run `./patch.sh` to apply `patch.diff` directly to the checked-out submodule.
The script is idempotent and reports when the patch is already applied.

Project-specific changes are intentionally small:

- `LUA_NO_FILESYSTEM` removes file-loading declarations and implementations,
  plus the base-library `loadfile` and `dofile` entries.
- The locale decimal point is fixed to `.` for this embedded target.
- Picolibc routes Lua's standard output to the kernel UART.
- The build compiles the core, auxiliary library, base library, string
  library, and math library. Filesystem, package, and OS modules are omitted.

Clone this project with `git clone --recurse-submodules`, or initialize an
existing checkout with `git submodule update --init --recursive`.

To update Lua, restore the submodule, fetch and check out the new official tag
inside `src/`, stage the resulting submodule gitlink, regenerate `patch.diff`
against that tag, update the version and commit above, and run `./patch.sh`.
