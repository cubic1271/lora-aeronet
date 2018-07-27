#ifndef _AERONET_STATS_H
#define _AERONET_STATS_H

#include <stdint.h>

typedef struct aeronet_stats_t {
    uint32_t   rssi[512];
    float      snr[512];
    float      lat[512];
    float      lng[512];
    uint16_t   ring_offset;

    uint32_t   rx_frames;
    uint32_t   rx_bytes;

    uint32_t   tx_frames;
    uint32_t   tx_bytes;
} aeronet_stats_t;

void aeronet_stats_init();

#endif
