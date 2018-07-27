#ifndef _AERONET_DISPLAY_H
#define _AERONET_DISPLAY_H

#include "SSD1306.h"

typedef struct aeronet_display_t {
    SSD1306*  display;
    uint32_t  ts_low;
    uint32_t  ts_high;
} aeronet_display_t;

/**
Initializes and clears the display as needed.

@param display target display to be initialized and used
*/
void aeronet_display_init(SSD1306* display);

/**
Called as a part of the main loop - performs any necessary updates.
*/
void aeronet_display_update();

aeronet_display_t* aeronet_display();

#endif
