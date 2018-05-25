#include "Arduino.h"
#include "Bounce.h"
#include "Rotary.h"

class SwitchRotary : public Rotary
{
  Bounce mSW;
  uint8_t mIdent;

public:
  SwitchRotary(uint8_t ident, uint8_t pin1, uint8_t pin2, uint8_t sw) :
    Rotary(pin1,pin2), mSW(sw,10), mIdent(ident<<4)
  {
      pinMode(sw, INPUT);
#ifdef ENABLE_PULLUPS
      digitalWrite(sw, HIGH);
#endif
  }

  inline __attribute__((always_inline)) uint8_t switchProcess()
  {
    return mSW.update() * (mSW.fallingEdge()+1);
  }

  inline __attribute__((always_inline)) uint8_t process()
  {
    return mIdent + 
          ( switchProcess() << 2 ) + 
          (Rotary::process()>>4);
  }
};

void printBinary(byte inByte)
{
  
  Serial.println(inByte,BIN);
}

SwitchRotary r(0, 2, 3, 4);
SwitchRotary r1(1, 5, 6, 7);
SwitchRotary r2(2, 8, 9, 10);
SwitchRotary r3(3, 11, 12, 13);
SwitchRotary r4(4, A0, A1, A2);
SwitchRotary r5(5, A3, A4, A5);

void setup() {
  Serial.begin(19200);
}

//void SEND(SwitchRotary& X) { uint8_t rot = X.process(); if ( rot & 15 ) printBinary(rot); }
#define SEND(X) { uint8_t rot = (X).process(); if ( rot & 15 ) Serial.write(rot); }
//#define SEND(X) { uint8_t rot = (X).process(); if ( rot & 15 ) printBinary(rot); }

void loop() {
  SEND(r);
  SEND(r1);
  SEND(r2);
  SEND(r3);
  SEND(r4);
  SEND(r5);
}

