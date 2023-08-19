qemu-system-aarch64 \
  -M virt \
  -cpu cortex-a72 \
  -smp 4 \
  -m 1024 \
  -nographic \
  -M dumpdtb=qemu.dtb
dtc -I dtb -O dts qemu.dtb
rm qemu.dtb
