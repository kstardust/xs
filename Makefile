LLVMPATH = /opt/homebrew/opt/llvm/bin
LD = ld.lld
CC = $(LLVMPATH)/clang
BASE_CFLAGS = -g --target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc -nostdlib
CFLAGS = $(BASE_CFLAGS)
LDFLAGS= -m aarch64elf -nostdlib -T link.ld
OBJS = boot/_boot.o kernel/kernel.o dev/dev.o lib/lib.o
MAKEVARS = CC="$(CC)" LD="$(LD)" BASE_CFLAGS="$(BASE_CFLAGS)" LLVMPATH="$(LLVMPATH)"

all: kernel8.img

boot/_boot.o:
	(make -C boot $(MAKEVARS))

kernel/kernel.o:
	(make -C kernel $(MAKEVARS))

dev/dev.o:
	(make -C dev $(MAKEVARS))

lib/lib.o:
	(make -C lib $(MAKEVARS))

kernel8.img: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel.elf
	$(LLVMPATH)/llvm-objcopy -O binary kernel.elf kernel.img

clean:
	(cd boot; make clean)
	(cd kernel; make clean)
	(cd dev; make clean)
	(cd lib; make clean)
	rm kernel8.elf *.o kernel.img 2> /dev/null || true
