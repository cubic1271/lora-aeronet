#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

#include <SPI.h>
#include <LoRa.h>
#include "stats.h"
#include "display.h"
// #include "SSD1306.h"

SSD1306 display(0x3c, 4, 15);

// ADC? Battery voltage
const uint8_t vbatPin = 34;
float VBAT;  // battery voltage from ESP32 ADC read

int ctr = 0;
char sbuf[512];

void setup() {
    SPI.begin(5,19,27,18);

    aeronet_display_init(&display);
    aeronet_radio_init();
    aeronet_vt100_init(&Serial);

    pinMode(vbatPin, INPUT);
    VBAT = (120.0/20.0) * (float)(analogRead(vbatPin)) / 1024.0; // LiPo battery voltage in volts
}

void loop() {

}
