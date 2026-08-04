# OpenLibm import

The `src`, `include`, and `aarch64` directories and `LICENSE.md` are imported
from JuliaMath/OpenLibm commit
`82e90aef0657289192efe77be89791c07dea0775` (OpenLibm 0.8.0).

Only the real double-precision functions required by Lua are built. Complex,
float, long-double, special-function, and host fenv sources are intentionally
excluded from this bare-metal profile.
