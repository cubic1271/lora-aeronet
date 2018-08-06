#ifndef _AERONET_RADIO_H
#define _AERONET_RADIO_H

#include <stdint.h>
#include "LoRa.h"

typedef enum aeronet_radio_mode_t {
    RADIO_MODE_LORA = 0,
    RADIO_MODE_GFSK = 1
} aeronet_radio_mode_t;

typedef struct aeronet_radio_t {
    uint32_t  ts_low;
    uint32_t  ts_high;

    uint32_t  center;

    // lora_fields
    uint32_t  spreading;
    uint32_t  bandwidth;
    uint32_t  codingRateDenominator;

    uint8_t   mode;
} aeronet_radio_t;

aeronet_radio_t* aeronet_radio();
int aeronet_radio_init();
void aeronet_radio_update();
float aeronet_radio_datarate();

#endif
