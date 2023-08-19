CFILES = $(wildcard *.c)
ASMFILES = $(wildcard *.S)
OFILES = $(CFILES:.c=.o)
ASMOFILES = $(ASMFILES:.S=.o)
LLVMPATH = /opt/homebrew/opt/llvm/bin
LD = $(LLVMPATH)/ld.lld
CC = $(LLVMPATH)/clang
CFLAGS = --target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc -nostdlib -I../include
LDFLAGS= -r

dev.o: $(OFILES) $(ASMOFILES)
	$(LD) $(LDFLAGS) $(OFILES) $(ASMOFILES) -o dev.o

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o
