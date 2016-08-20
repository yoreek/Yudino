# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

#ARDUINO_QUIET = 1
ROOT_DIR = $(HOME)/robot

BOARD_TAG = uno
#BOARD_TAG    = mega
#BOARD_SUB = atmega2560
#BOARD_TAG = nano
#BOARD_SUB = atmega328

ARDUINO_DIR = $(ROOT_DIR)/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF = /etc/avrdude.conf
ARDUINO_PORT = /dev/ttyACM0

MONITOR_BAUDRATE = 57600
MONITOR_CMD = picocom

ARDUINO_LIBS = DebugUtil                                                \
               StringUtil                                               \
               Time                                                     \
               SPI                                                      \
               Wire                                                     \
               Wire                                                     \
               SdFat                                                    \
               Ethernet                                                 \
               Yudino                                                   \
               Low-Power

CXXFLAGS = -std=c++11 -std=c++1y                                        \
           -fno-move-loop-invariants -Wall -Werror                      \
           -U__PROG_TYPES_COMPAT__                                      \
           -DWITH_DEBUG -DUSE_STRING_UTIL -DUSE_PROGMEM
# Enable float type on sprintf
#LDFLAGS=-lprintf_flt -lm
# Fix bug with segfault during compilation
#CXXFLAGS=-fno-move-loop-invariants

include $(ROOT_DIR)/Arduino-Makefile/Arduino.mk
