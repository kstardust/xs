qemu-system-aarch64 -gdb tcp::2234 -S \
  -M virt \
  -cpu cortex-a72 \
  -smp 4 \
  -m 1024 \
  -nographic \
  -kernel kernel.elf \
  -serial mon:stdio \
  -drive if=none,file=disk.img,format=raw  \
  -device virtio-blk-device,drive=disk,id=virtio-blk-disk\
  -global virtio-mmio.force-legacy=false
#  -serial telnet:localhost:1234,server,nowait 
