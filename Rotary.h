#include "Arduino.h"

#include "direct_pin_read.h"

// Enable this to emit codes twice per step.
// #define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
  public:
    Rotary(uint8_t, uint8_t);
    uint8_t process();
  private:
    uint8_t state;
    volatile IO_REG_TYPE * pin1_register;
    IO_REG_TYPE pin1_bitmask;
    volatile IO_REG_TYPE * pin2_register;
    IO_REG_TYPE pin2_bitmask;
};
