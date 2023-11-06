qemu-system-aarch64 \
  -M virt \
  -cpu cortex-a72 \
  -smp 4 \
  -m 1024 \
  -nographic \
  -drive if=none,id=disk,file=disk.img,format=raw\
  -device virtio-blk-device,drive=disk,id=virtio-blk-disk \
  -global virtio-mmio.force-legacy=false \
  -M dumpdtb=qemu.dtb
dtc -I dtb -O dts qemu.dtb
rm qemu.dtb
