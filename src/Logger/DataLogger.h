#pragma once
#ifndef _DATA_LOGGER_H_
#define _DATA_LOGGER_H_

#include <stdarg.h>
#include <SdFat.h>
#include <Time.h>

class DataLogger {
    public:
        DataLogger(
            SdFat         *sd,
            const char    *fileName,
            const char    *header = NULL
        ) :
            _sd(sd),
            _fileName(fileName),
            _header(header)
        {};

        void getRealFileName(char *realFileName);
        void log(const char *fmt, ...);
#ifdef F
        void log(const __FlashStringHelper *fmt, ...);
        void log_P(const char *fmt, ...);
#endif

    private:
        void           _log(const char *fmt, const char *fsfmt, va_list &args);
        bool           _openFile(File &file, time_t t);
        void           _closeFile(File &file, time_t t);
        SdFat         *_sd;
        const char    *_fileName;
        const char    *_header;
};

#endif
