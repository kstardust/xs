# Embedded Lua build. Run patch.sh before compiling.
CFILES = lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c lgc.c \
	llex.c lmem.c lobject.c lopcodes.c lparser.c lstate.c lstring.c \
	ltable.c ltm.c lundump.c lvm.c lzio.c lauxlib.c lbaselib.c \
	lstrlib.c lmathlib.c
BUILD_DIR = .build
OFILES = $(addprefix $(BUILD_DIR)/,$(CFILES:.c=.o))
CFLAGS = $(BASE_CFLAGS)
CFLAGS += -Isrc -I. -I../include -DLUA_FREESTANDING \
	-DLUA_NO_FILESYSTEM -DLUA_USE_C89 -MMD -MP
DEPS = $(OFILES:.o=.d)
LDFLAGS = -r

lua.o: $(OFILES)
	$(LD) $(LDFLAGS) $(OFILES) -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm lua.o 2> /dev/null || true

$(DEPS): ;

-include $(wildcard $(DEPS))
