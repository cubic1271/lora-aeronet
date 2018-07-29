#ifndef _AERONET_VT100_H
#define _AERONET_VT100_H

#include <Arduino.h>

typedef struct aeronet_vt100_t {
    HardwareSerial* serial;

    uint32_t ts_high;
    uint32_t ts_low;
} aeronet_vt100_t;

int aeronet_vt100_init(HardwareSerial* serial);

void aeronet_vt100_update();

#endif
