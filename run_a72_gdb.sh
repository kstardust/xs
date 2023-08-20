qemu-system-aarch64 -gdb tcp::2234 -S \
  -M virt \
  -cpu cortex-a72 \
  -smp 4 \
  -m 1024 \
  -nographic \
  -kernel kernel.elf \
  -serial mon:stdio
#  -serial telnet:localhost:1234,server,nowait 
