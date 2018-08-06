#include "vt100.h"

aeronet_vt100_t _vt100;

static const char* valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|/+-._!@#$^&*()[]{};'? ";
static void aeronet_shell();

static int aeronet_vt100_isvalid(int ch) {
    int i = 0;
    for(i = 0; i < strlen(valid); ++i) {
        if(ch == valid[i]) {
            return 1;
        }
    }

    return 0;
}

static const char* aeronet_level2str(aeronet_vt100_loglevel_t level) {
    switch(level) {
        case LOGLEVEL_TRACE:
            return "trace";
        case LOGLEVEL_DEBUG:
            return "debug";
        case LOGLEVEL_INFO:
            return "info";
        case LOGLEVEL_WARN:
            return "warn";
        case LOGLEVEL_ERROR:
            return "error";
        case LOGLEVEL_FATAL:
            return "fatal";
        default:
            return "???";
    }
}

aeronet_vt100_t* aeronet_vt100() {
    return &_vt100;
}

int aeronet_vt100_init(HardwareSerial* serial) {
    memset(&_vt100, 0, sizeof(aeronet_vt100_t));
    _vt100.serial = serial;
    _vt100.serial->begin(115200);
    _vt100.level = LOGLEVEL_INFO;
    aeronet_vt100_clear();
    aeronet_vt100_moveto(1, 3);
    aeronet_shell();
    return 0;
}

void aeronet_vt100_clear() {
    _vt100.serial->print(VT100_CLEAR_SCREEN);
    aeronet_vt100_moveto(1, 3);
}

void aeronet_vt100_clearline() {
    _vt100.serial->print(VT100_CLEAR_LINE);
}

void aeronet_vt100_moveto(int x, int y) {
    char sbuf[64];
    snprintf(sbuf, 64, "\033[%d;%dH", y, x);
    _vt100.serial->print(sbuf);
}

void aeronet_vt100_savecursor() {
    _vt100.serial->print(VT100_SAVE_CURSOR);
}

void aeronet_vt100_loadcursor() {
    _vt100.serial->print(VT100_LOAD_CURSOR);
}

void aeronet_log(aeronet_vt100_loglevel_t level, const char* format, ...) {
    va_list vptr;
    if(level < _vt100.level) {
        return;
    }
    uint64_t ts_comb = ((uint64_t)_vt100.ts_high << (uint64_t)32) | ((uint64_t)_vt100.ts_low);
    snprintf(_vt100.output_buf, CONSOLE_BUFSZ, "[%s:+%llu] ", aeronet_level2str(level), ts_comb);
    _vt100.serial->print(_vt100.output_buf);
    memset(_vt100.output_buf, 0, CONSOLE_BUFSZ);
    va_start(vptr, format);
    vsnprintf(_vt100.output_buf, CONSOLE_BUFSZ, format, vptr);
    va_end(vptr);
    _vt100.serial->print(_vt100.output_buf);
    _vt100.serial->print("\r\n");
    memset(_vt100.output_buf, 0, CONSOLE_BUFSZ);
}

void aeronet_logstr(aeronet_vt100_loglevel_t level, const char* str) {
    aeronet_log(level, "%s", str);
}

void aeronet_print(const char* format, ...) {
    va_list vptr;
    memset(_vt100.output_buf, 0, CONSOLE_BUFSZ);
    va_start(vptr, format);
    vsnprintf(_vt100.output_buf, CONSOLE_BUFSZ, format, vptr);
    va_end(vptr);
    _vt100.serial->print(_vt100.output_buf);
    _vt100.serial->print("\r\n");
    memset(_vt100.output_buf, 0, CONSOLE_BUFSZ);
}

void aeronet_printstr(const char* str) {
    aeronet_print("%s", str);
}

static void aeronet_shell() {
    aeronet_vt100_savecursor();
    aeronet_vt100_moveto(1, 1);
    aeronet_vt100_clearline();
    _vt100.serial->print("************ AeroNet Shell ************");
    aeronet_vt100_moveto(1, 2);
    aeronet_vt100_clearline();
    _vt100.serial->print(">> ");
    _vt100.serial->print(_vt100.console_buf);
    aeronet_vt100_loadcursor();
}

void aeronet_vt100_update() {
    uint32_t curr = micros();
    if(curr < _vt100.ts_low) {
        _vt100.ts_high++;
    }
    _vt100.ts_low = curr;

    uint8_t input = 0;
    while(_vt100.serial->available()) {
        _vt100.input_buf[_vt100.input_idx] = _vt100.serial->read();
        if(_vt100.input_buf[_vt100.input_idx] == VTCHAR_BKSP || _vt100.input_buf[_vt100.input_idx] == VTCHAR_DEL) {
            if(_vt100.console_idx > 0) {
                --_vt100.console_idx;
            }
            _vt100.console_buf[_vt100.console_idx] = 0;
        }
        else if(_vt100.input_buf[_vt100.input_idx] == '\r') {
            if(_vt100.console_idx > 0) {
                aeronet_vt100_command(_vt100.console_buf);
                memset(_vt100.console_buf, 0, CONSOLE_BUFSZ);
                _vt100.console_idx = 0;
            }
        }
        else if(aeronet_vt100_isvalid(_vt100.input_buf[_vt100.input_idx])) {
            _vt100.console_buf[_vt100.console_idx] = _vt100.input_buf[_vt100.input_idx];
            if(_vt100.console_idx < CONSOLE_BUFSZ) {
                ++_vt100.console_idx;
            }
        }
        else {
        }

        input = 1;
    }

    if(input) {
        aeronet_shell();
    }


}
