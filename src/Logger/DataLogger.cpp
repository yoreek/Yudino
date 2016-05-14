#ifndef WITH_LOGGER_DEBUG
#undef WITH_DEBUG
#endif
#include <DebugUtil.h>
#include <stdio.h>
#include <stdarg.h>
#include <Time.h>
#include <StringUtil.h>
#include "DataLogger.h"

#ifndef MAX_PATH_LEN
#define MAX_PATH_LEN 256
#endif

void DataLogger::getRealFileName(char *realFileName) {
    StringUtil::sprintf(realFileName, _fileName);
}

bool DataLogger::_openFile(File &file, time_t t) {
    char    realFileName[MAX_PATH_LEN];
    char   *p;

    getRealFileName(realFileName);

    DEBUG("real file: %s", realFileName);

    if (_sd->exists(realFileName)) {
        DEBUG("file exists, open file");
        if (!file.open(realFileName, O_WRITE | O_AT_END)) {
            DEBUG("Cannot open file: %s", realFileName);
            return false;
        }
    }
    else {
        DEBUG("not exists");
        if ((p = strrchr(realFileName, '/')) != NULL && (p != realFileName)) {
            *p = '\0';
            if (!_sd->exists(realFileName)) {
                DEBUG("create dir: %s", realFileName);
                if (!_sd->mkdir(realFileName, true))
                    return false;
            }
            *p = '/';
        }
        if (!file.open(realFileName, O_CREAT | O_APPEND | O_WRITE)) {
            DEBUG("Cannot create file: %s", realFileName);
            return false;
        }
        if (_header != NULL)
            file.println(_header);
    }

    return true;
}

void DataLogger::_closeFile(File &file, time_t t) {
    file.timestamp(T_WRITE, year(t), month(t), day(t), hour(t), minute(t), second(t));    // edit date modified
    file.timestamp(T_ACCESS, year(t), month(t), day(t), hour(t), minute(t), second(t));   // edit date accessed

    file.flush();
    file.close();
}

void DataLogger::_log(const char *fmt, const char *fsfmt, va_list &args) {
    File    file;
    time_t  t = now();

    if (_openFile(file, t)) {
#ifdef F
        if (fmt != NULL) {
            StringUtil::vfprintf(file, fmt, args);
        }
        else {
            StringUtil::vfprintf(file, (const __FlashStringHelper *) fsfmt, args);
        }
#else
        StringUtil::vfprintf(file, fmt, args);
#endif
        file.println();

        _closeFile(file, t);
    }
}

void DataLogger::log(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    _log(fmt, NULL, args);
    va_end(args);
}

#ifdef F
void DataLogger::log(const __FlashStringHelper *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    _log(NULL, (const char *) fmt, args);
    va_end(args);
}

void DataLogger::log_P(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    _log(NULL, fmt, args);
    va_end(args);
}
#endif
