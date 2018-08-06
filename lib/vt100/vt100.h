#ifndef _AERONET_VT100_H
#define _AERONET_VT100_H

#include <Arduino.h>

#define CONSOLE_BUFSZ   (256)

#define VTCHAR_BKSP         (8)
#define VTCHAR_DEL          (127)

#define VT100_QUERY_POS     "\033[6n"
#define VT100_SAVE_CURSOR   "\033[s"
#define VT100_LOAD_CURSOR   "\033[u"
#define VT100_CLEAR_LINE    "\033[2K"
#define VT100_CLEAR_SCREEN  "\033[2J"

typedef enum aeronet_vt100_loglevel_t {
    LOGLEVEL_TRACE,
    LOGLEVEL_DEBUG,
    LOGLEVEL_INFO,
    LOGLEVEL_WARN,
    LOGLEVEL_ERROR,
    LOGLEVEL_FATAL
} aeronet_vt100_loglevel_t;

typedef struct aeronet_vt100_t {
    HardwareSerial*            serial;
    uint32_t                   ts_high;
    uint32_t                   ts_low;
    uint16_t                   console_idx;
    uint16_t                   input_idx;
    char                       console_buf[CONSOLE_BUFSZ];
    char                       output_buf[CONSOLE_BUFSZ];
    char                       input_buf[16];
    aeronet_vt100_loglevel_t   level;
} aeronet_vt100_t;

typedef int (*aeronet_vt100_callback_t)(const int argc, const char* argv[]);

typedef struct aeronet_vt100_cmdentry_t {
    const char*                command;
    aeronet_vt100_callback_t   callback;
} aeronet_vt100_cmdentry_t;

aeronet_vt100_t* aeronet_vt100();
int aeronet_vt100_init(HardwareSerial* serial);

int aeronet_vt100_command(char* command);

void aeronet_vt100_moveto(int x, int y);
void aeronet_vt100_savecursor();
void aeronet_vt100_loadcursor();
void aeronet_vt100_clear();
void aeronet_vt100_clearline();

void aeronet_printstr(const char* str);
void aeronet_logstr(aeronet_vt100_loglevel_t level, const char* str);
void aeronet_print(const char* format, ...);
void aeronet_log(aeronet_vt100_loglevel_t level, const char* format, ...);
void aeronet_vt100_update();

#endif
