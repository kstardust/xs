#include <virtio.h>
#include <common.h>
#include <string.h>


int
virtio_dev_init(virtio_regs *v)
{
    if (v->MagicValue != VIRTIO_MAGIC) {
        printf("virtio dev at 0x%x wrong magic number: 0x%x\n", v, v->MagicValue);
        return -1;
    }

    if (v->Version != VIRTIO_VERSION) {
        printf("virtio dev at 0x%x wrong version: 0x%x\n", v, v->Version);
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
