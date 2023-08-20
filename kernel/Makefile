CFILES = $(wildcard *.c)
ASMFILES = $(wildcard *.S)
OFILES = $(CFILES:.c=.o)
ASMOFILES = $(ASMFILES:.S=.o)
LLVMPATH = /opt/homebrew/opt/llvm/bin
LD = $(LLVMPATH)/ld.lld
CC = $(LLVMPATH)/clang
CFLAGS = -g --target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc -nostdlib -I../include
LDFLAGS= -r



kernel.o: $(OFILES) $(ASMOFILES)
	$(LD) $(LDFLAGS) $(OFILES) $(ASMOFILES) -o kernel.o

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o 2> /dev/null || true
