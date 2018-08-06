#include "radio.h"

// GPIO5 — SX1278’s SCK
// GPIO19 — SX1278’s MISO
// GPIO27 — SX1278’s MOSI
// GPIO18 — SX1278’s CS
// GPIO14 — SX1278’s RESET
// GPIO26 — SX1278’s IRQ(Interrupt Request)

#define SS 18
#define RST 14
#define DI0 26

static aeronet_radio_t _radio;

int aeronet_radio_init() {
    memset(&_radio, 0, sizeof(aeronet_radio_t));
    _radio.center = 915000000.00;
    _radio.spreading = 8;
    _radio.bandwidth = 125000;
    _radio.codingRateDenominator = 8;
    LoRa.setPins(SS,RST,DI0);
    LoRa.setSpreadingFactor(_radio.spreading);
    LoRa.setSignalBandwidth(_radio.bandwidth);
    LoRa.setCodingRate4(_radio.codingRateDenominator);

    if (!LoRa.begin(_radio.center, true)) {
        return -1;
    }

    return 0;
}

aeronet_radio_t* aeronet_radio() {
    return &_radio;
}

float aeronet_radio_datarate() {
    return _radio.spreading
            * (_radio.bandwidth / (float)(1 << _radio.spreading))
            * (4.0 / (float)_radio.codingRateDenominator);
}

void aeronet_radio_update() {

}
