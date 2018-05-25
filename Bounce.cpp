
// Please read Bounce.h for information about the liscence and authors

#include "Arduino.h"
#include "Bounce.h"


Bounce::Bounce(uint8_t pin,unsigned long interval_millis)
{
	interval(interval_millis);
	previous_millis = millis();
 
  pin_register = PIN_TO_BASEREG(pin);
  pin_bitmask = PIN_TO_BITMASK(pin);
  
  noInterrupts();
  state = DIRECT_PIN_READ(pin_register,pin_bitmask);
  interrupts();
}

void Bounce::interval(unsigned long interval_millis)
{
  this->interval_millis = interval_millis;
  this->rebounce_millis = 0;
}

void Bounce::rebounce(unsigned long interval)
{
	 this->rebounce_millis = interval;
}



int Bounce::update()
{
	if ( debounce() ) {
        rebounce(0);
        return stateChanged = 1;
    }

     // We need to rebounce, so simulate a state change
     
	if ( rebounce_millis && (millis() - previous_millis >= rebounce_millis) ) {
        previous_millis = millis();
		 rebounce(0);
		 return stateChanged = 1;
	}

	return stateChanged = 0;
}


unsigned long Bounce::duration()
{
  return millis() - previous_millis;
}


int Bounce::read()
{
	return (int)state;
}


// Protected: debounces the pin
int Bounce::debounce() {
  
  noInterrupts();
  uint8_t newState = DIRECT_PIN_READ(pin_register,pin_bitmask);
  interrupts();
  
	if (state != newState ) {
  		if (millis() - previous_millis >= interval_millis) {
  			previous_millis = millis();
  			state = newState;
  			return 1;
	}
  }
  
  return 0;
	
}

// The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.
bool  Bounce::risingEdge() { return stateChanged && state; }
// The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off. 
bool  Bounce::fallingEdge() { return stateChanged && !state; }

