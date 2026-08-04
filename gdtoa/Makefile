CFILES = dmisc.c dtoa.c gdtoa.c gethex.c gmisc.c hd_init.c hexnan.c \
	misc.c smisc.c strtod.c sum.c ulp.c g__fmt.c g_dfmt.c \
	numeric_conv.c helpers.c
OFILES = $(CFILES:.c=.o)
CFLAGS = $(BASE_CFLAGS) -I../include -I../openlibm/include -I. \
	-DNO_FENV_H -fno-strict-aliasing
LDFLAGS = -r

libgdtoa.o: $(OFILES)
	$(LD) $(LDFLAGS) $(OFILES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o 2> /dev/null || true
