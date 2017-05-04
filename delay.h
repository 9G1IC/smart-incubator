#include <avr/interrupt.h>
//used to set delay
volatile uint8_t timeElapsed;
volatile uint8_t secondsElapsed;

int  _delay_msec(double duration);//Millisecond delay
int  _delay_usec(double duration);//Microsecond delay
int  _delay_sec(double duration);//Second delay



