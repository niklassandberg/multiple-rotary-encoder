# Multiple-rotary-encoder

## Configuration/Setup

Just install Arduino IDE https://www.arduino.cc/en/Main/Software and clone this project. 

### Hardware

* runnable atmega328p or compatible.
* 5 to 3.3 voltage correlation between atmega and teensy UART.

### Format

Comunication is made throu Tx,Rx. 

The format is as follows:
```
First four most significant bits is the RE identification.
Two second bits indicates if RE was pressed or not.
The two least significant bits indicates if RE was rotated counter- or clockwise.
```

Examples:

|    Message       |              Interpretation                        |
------------------ | ----------------------------------------------------
| `0000` `10` `00` | RE id 0 was pressed                                |
------------------ | ----------------------------------------------------
| `0001` `10` `10` | RE id 1 was pressed and rotated counter clockwise. |
------------------ | ----------------------------------------------------
| `0010` `01` `01` | RE id 2 was released and rotated clockwise.        | 
------------------ | ----------------------------------------------------

