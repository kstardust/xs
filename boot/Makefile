CFILES = $(wildcard *.c)
ASMFILES = $(wildcard *.S)
OFILES = $(CFILES:.c=.o)
ASMOFILES = $(ASMFILES:.S=.o)
CFLAGS = $(BASE_CFLAGS)
CFLAGS += -I../include
LDFLAGS= -r

_boot.o: $(OFILES) $(ASMOFILES)
	$(LD) $(LDFLAGS) $(OFILES) $(ASMOFILES) -o _boot.o

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm *.o 2> /dev/null || true
