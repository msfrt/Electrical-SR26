#include "gio.h"

uint32_t gioGetBit(uint8_t pin) {
    return digitalRead(pin);
}