#define F_CPU 16000000UL
#include <util/delay.h>
#include "delay.h"
//This uses the interrupts to determine delay
//Here, the interrupts generates the clock signal that is used to count
//when the count reaches the set value, it then triggers
//

//Microseconds delay
int _delay_usec(double duration){
	for(int start=0;start<duration;start++)
	_delay_us(1);
	return 0;
}
//Milliseconds Delay	
int  _delay_msec(double duration){
	for(int start=0;start<duration;start++)
	_delay_ms(1);
return 0;
}
//Seconds delay
int  _delay_sec(double duration){
	for(int start=0;start<duration;start++)
	_delay_ms(1000);
return 0;
}

//Generate a one second time base


