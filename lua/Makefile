# FreeBSD stand/liblua profile: upstream core plus the auxiliary, base, and
# string libraries. Loader modules requiring libsa filesystems are omitted.
CFILES = lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c lgc.c \
	llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c \
	ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c lbaselib.c \
	lstrlib.c lmathlib.c lstd.c
ASMFILES =
OFILES = $(CFILES:.c=.o)
ASMOFILES = $(ASMFILES:.S=.o)
CFLAGS = $(BASE_CFLAGS)
CFLAGS += -I../include -DLUA_FREESTANDING \
	-DLUA_NO_FILESYSTEM -DLUA_USE_C89 -include lstd.h
LDFLAGS= -r

lua.o: $(OFILES) $(ASMOFILES)
	$(LD) $(LDFLAGS) $(OFILES) $(ASMOFILES) -o lua.o

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm *.o 2> /dev/null || true
