#include "vt100.h"

#define AERONET_MAXCMD   (16)

static int aerocmd_do_help(int argc, const char* argv[]);
static int aerocmd_do_loglevel(int argc, const char* argv[]);

static aeronet_vt100_cmdentry_t _cmdtable[] = {
    {
        "help",
        aerocmd_do_help
    },
    {
        "loglevel",
        aerocmd_do_loglevel
    },
    {
        "",
        NULL
    }
};

static int aerocmd_do_help(int argc, const char* argv[]) {
    int i = 0;
    aeronet_printstr("Known commands:");
    while(_cmdtable[i].callback != NULL) {
        aeronet_print("  %s", _cmdtable[i].command);
        ++i;
    }
    return 0;
}

static int aerocmd_do_loglevel(int argc, const char* argv[]) {
    if(argc >= 2) {
        if(!strcmp(argv[1], "trace")) {
            aeronet_vt100()->level = LOGLEVEL_TRACE;
        }
        else if(!strcmp(argv[1], "debug")) {
            aeronet_vt100()->level = LOGLEVEL_DEBUG;
        }
        else if(!strcmp(argv[1], "info")) {
            aeronet_vt100()->level = LOGLEVEL_INFO;
        }
        else if(!strcmp(argv[1], "warn")) {
            aeronet_vt100()->level = LOGLEVEL_WARN;
        }
        else if(!strcmp(argv[1], "error")) {
            aeronet_vt100()->level = LOGLEVEL_ERROR;
        }
        else if(!strcmp(argv[1], "fatal")) {
            aeronet_vt100()->level = LOGLEVEL_FATAL;
        }
        else {
            aeronet_logstr(LOGLEVEL_ERROR, "Invalid argument to 'loglevel' - options are trace, debug, info, warn, error, or fatal");
        }
    }
    else {
        aeronet_logstr(LOGLEVEL_ERROR, "'loglevel' requires an argument - trace, debug, info, warn, error, or fatal");
    }
    return 0;
}

int aeronet_vt100_command(char* command) {
    int i = 0;
    int matched = 0;
    char* saveptr;
    char* cmd[AERONET_MAXCMD];
    int argc = 1;
    char* base = strtok_r(command, " ", &saveptr);
    char* curr = strtok_r(NULL, " ", &saveptr);
    while(curr != NULL) {
        cmd[argc] = curr;
        ++argc;
        curr = strtok_r(NULL, " ", &saveptr);
        if(argc >= AERONET_MAXCMD) {
            curr = NULL;
        }
    }
    aeronet_log(LOGLEVEL_TRACE, "Command: %s [+%d arguments]", base, argc);
    while(_cmdtable[i].callback != NULL && !matched) {
        if(!strcmp(_cmdtable[i].command, base)) {
            if(_cmdtable[i].callback != NULL) {
                aeronet_log(LOGLEVEL_DEBUG, "Calling command handler for: %s", base);
                _cmdtable[i].callback(argc, (const char**)cmd);
                matched = 1;
            }
        }
        ++i;
    }
    if(!matched) {
        aeronet_log(LOGLEVEL_WARN, "Unknown command: %s", base);
    }
    return 0;
}
