#include "display.h"

static aeronet_display_t  _display_info;

void aeronet_display_init(SSD1306* display) {
    memset(&_display_info, 0, sizeof(aeronet_display_t));
    _display_info.display = display;
    _display_info.ts_low = micros();
}

void aeronet_display_update() {
    uint32_t ts = micros();
    if(ts < _display_info.ts_low) {
        _display_info.ts_high ++;
        _display_info.ts_low = ts;
    }


}
