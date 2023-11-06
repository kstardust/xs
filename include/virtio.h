#ifndef  _VIRTIO_H
#define  _VIRTIO_H

#include <ctypes.h>

#define VIRTIO_FIRST   0xa000000        // from dts
#define VIRTIO_LAST    0xa003e00
#define VIRTIO_SIZE    0x200

// http://docs.oasis-open.org/virtio/virtio/v1.0/cs04/virtio-v1.0-cs04.html
#define VIRTIO_MAGIC 0x74726976
#define VIRTIO_VERSION 0x2
#define VIRTIO_VERSION_LEGACY 0x1

#define VIRTIO_BLOCK_DEVICE 0x2


typedef volatile struct __attribute__((packed)) {
    uint32_t MagicValue;
    uint32_t Version;
    uint32_t DeviceID;
    uint32_t VendorID;
    uint32_t DeviceFeatures;
    uint32_t DeviceFeaturesSel;
    uint32_t _reserved0[2];
    uint32_t DriverFeatures;
    uint32_t DriverFeaturesSel;
    uint32_t _reserved1[2];
    uint32_t QueueSel;
    uint32_t QueueNumMax;
    uint32_t QueueNum;
    uint32_t _reserved2[2];
    uint32_t QueueReady;
    uint32_t _reserved3[2];
    uint32_t QueueNotify;
    uint32_t _reserved4[3];
    uint32_t InterruptStatus;
    uint32_t InterruptACK;
    uint32_t _reserved5[2];
    uint32_t Status;
    uint32_t _reserved6[3];
    uint32_t QueueDescLow;
    uint32_t QueueDescHigh;
    uint32_t _reserved7[2];
    uint32_t QueueAvailLow;
    uint32_t QueueAvailHigh;
    uint32_t _reserved8[2];
    uint32_t QueueUsedLow;
    uint32_t QueueUsedHigh;
    uint32_t _reserved9[21];
    uint32_t ConfigGeneration;
    uint32_t Config[0];
} virtio_regs;

void virtio_init();
    
#endif


