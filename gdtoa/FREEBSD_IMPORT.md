# FreeBSD gdtoa import

The conversion sources are imported from FreeBSD revision
`5c4e8a6310973f22eb76835f1b0d5ba5dd9df2f7`, primarily from
`contrib/gdtoa`, with the AArch64 machine headers from `lib/libc/aarch64`.

The adaptation fixes the locale to the C locale, removes libc threading,
fenv, and errno integration, and supplies Lua hooks for decimal parsing and
formatting. It does not add any filesystem or stream API.
