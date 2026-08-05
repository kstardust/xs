LLVMPATH = /opt/homebrew/opt/llvm/bin
LD = ld.lld
CC = $(LLVMPATH)/clang
PICOLIBC_BUILD = $(CURDIR)/build/picolibc
CLANG_RESOURCE = $(shell $(CC) --print-resource-dir)
BASE_CFLAGS = -g --target=aarch64-elf -Wall -O2 -ffreestanding -nostdinc \
	-nostdlib -isystem $(PICOLIBC_BUILD)/picolibc/include \
	-isystem $(CLANG_RESOURCE)/include
CFLAGS = $(BASE_CFLAGS)
LDFLAGS= -m aarch64elf -nostdlib -T link.ld
OBJS = boot/_boot.o kernel/kernel.o dev/dev.o lib/lib.o lua/lua.o
LIBS = $(PICOLIBC_BUILD)/libc.a
MAKEVARS = CC="$(CC)" LD="$(LD)" BASE_CFLAGS="$(BASE_CFLAGS)" LLVMPATH="$(LLVMPATH)"

.PHONY: all clean clean-all

all: kernel8.img

boot/_boot.o:
	(make -C boot $(MAKEVARS))

kernel/kernel.o:
	(make -C kernel $(MAKEVARS))

dev/dev.o:
	(make -C dev $(MAKEVARS))

lib/lib.o:
	(make -C lib $(MAKEVARS))

lua/lua.o:
	(make -C lua $(MAKEVARS))

$(PICOLIBC_BUILD)/CMakeCache.txt: picolibc-toolchain.cmake
	cmake -S picolibc -B $(PICOLIBC_BUILD) \
		-DCMAKE_TOOLCHAIN_FILE=$(CURDIR)/picolibc-toolchain.cmake \
		-DCMAKE_BUILD_TYPE=MinSizeRel

$(PICOLIBC_BUILD)/libc.a: $(PICOLIBC_BUILD)/CMakeCache.txt
	cmake --build $(PICOLIBC_BUILD) --target c

kernel8.img: $(PICOLIBC_BUILD)/libc.a $(OBJS)
	$(LD) $(LDFLAGS) --start-group $(OBJS) $(LIBS) --end-group -o kernel.elf
	$(LLVMPATH)/llvm-objcopy -O binary kernel.elf kernel.img

clean:
	(cd boot; make clean)
	(cd kernel; make clean)
	(cd dev; make clean)
	(cd lib; make clean)
	(cd lua; make clean)
	rm kernel.elf kernel8.elf *.o kernel.img 2> /dev/null || true

clean-all: clean
	cmake --build $(PICOLIBC_BUILD) --target clean 2> /dev/null || true
