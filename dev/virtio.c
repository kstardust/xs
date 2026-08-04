#include <virtio.h>
#include <common.h>
#include <stdio.h>
#include <string.h>


int
virtio_dev_init(virtio_regs *v)
{
    if (v->MagicValue != VIRTIO_MAGIC) {
        printf("virtio dev at %p wrong magic number: 0x%x\n", (void *)v,
            v->MagicValue);
        return -1;
    }

    if (v->Version != VIRTIO_VERSION) {
        printf("virtio dev at %p wrong version: 0x%x\n", (void *)v,
            v->Version);
        return -1;
    }

    if (v->DeviceID == 0) {
        return 0;
    }

    printf("deivce found type: %d\n", v->DeviceID);

    return 0;
}

void
virtio_init()
{

    for (uint64_t addr = VIRTIO_FIRST; addr <= VIRTIO_LAST; addr+=VIRTIO_SIZE) {
        virtio_regs *v = (virtio_regs*)addr;
        virtio_dev_init(v);
    }

}
