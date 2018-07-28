#include "display.h"

static aeronet_display_t  _display_info;

void aeronet_display_init(SSD1306* display) {
    memset(&_display_info, 0, sizeof(aeronet_display_t));
    _display_info.display = display;
    _display_info.ts_low = micros();

    pinMode(16,OUTPUT);
    digitalWrite(16, LOW); // set GPIO16 low to reset OLED
    delay(50);
    digitalWrite(16, HIGH);

    display->init();
    display->flipScreenVertically();
    display->setFont(ArialMT_Plain_24);
    display->setTextAlignment(TEXT_ALIGN_CENTER);

    display->drawString(65, 0, "A e r o");
    display->drawString(65, 30, "\\-/ N e t");
    display->display();

    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);

    delay(1500);

    display->clear();
    display->display();
}

void aeronet_display_update() {
    uint32_t ts = micros();
    if(ts < _display_info.ts_low) {
        _display_info.ts_high ++;
        _display_info.ts_low = ts;
    }


}
