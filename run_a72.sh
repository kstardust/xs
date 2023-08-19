qemu-system-aarch64 \
  -M virt \
  -cpu cortex-a72 \
  -smp 4 \
  -m 1024 \
  -nographic \
  -kernel kernel.img \
  -serial mon:stdio
#  -serial telnet:localhost:1234,server,nowait 
