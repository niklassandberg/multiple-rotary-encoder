# Multiple-rotary-encoder

## Configuration/Setup

* Install Arduino IDE https://www.arduino.cc/en/Main/Software and clone this project.
* If Arduino usb2serial is used as programmer choose board "Arduino Por or Pro Mini" in Arduino IDE and correct processor. This should not need to be documented here but apperantly it is hard to find this info.

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

|    Byte       |              Description                         |
------------------ | ----------------------------------------------------
| 0000 10 00 | RE id 0 was pressed                                |
| 0001 10 10 | RE id 1 was pressed and rotated counter clockwise. |
| 0010 01 01 | RE id 2 was released and rotated clockwise.        | 

