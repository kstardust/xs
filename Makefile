LLVMPATH = /opt/homebrew/opt/llvm/bin
LD = $(LLVMPATH)/ld.lld
CC = $(LLVMPATH)/clang
CFLAGS = -g --target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS= -m aarch64elf -nostdlib -T link.ld
OBJS = boot/_boot.o kernel/kernel.o dev/dev.o lib/lib.o
all: kernel8.img

boot/_boot.o:
	(cd boot; make)

kernel/kernel.o:
	(cd kernel; make)

dev/dev.o:
	(cd dev; make)

lib/lib.o:
	(cd lib; make)

kernel8.img: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel.elf
	$(LLVMPATH)/llvm-objcopy -O binary kernel.elf kernel.img

clean:
	(cd boot; make clean)
	(cd kernel; make clean)
	(cd dev; make clean)
	(cd lib; make clean)
	rm kernel8.elf *.o *.img 2> /dev/null || true
