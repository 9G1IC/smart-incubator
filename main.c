//#include "lcd.h"
#include "test.h"
#include "state.h"
#include "init.h"
#include "hardware.h"
#include "lcd.h"
#include <avr/interrupt.h>
#include "delay.h"
#include <stdlib.h>
#define test
//Main
//TODO:


ISR(TIMER0_COMPB_vect){//Reader
	static int sign=0;
	isrTestA0 >= READER?sign=0:(isrTestA0 <= 0?sign=1:0);
	sign == 0?isrTestA0--:isrTestA0++;
#ifdef test
	//Calculate moving average
	
#else
	//Take a reading and save them in the structures
	dht_read_data(sensorData,&t->currentTemperature,&h->currentHumidity);
#endif
		movingAverage(t,h);
		//This is used to simulate a timer or softclock
if(interrupt ==TRUE || timer >= 1000.00){
	timer=0;
	//reset the interrupt flag
	interrupt=FALSE;
}
else{
//count
timer+=0.001;
}
	if(timer >= 200.00){//Time out
		notifictions();
	}
}

ISR(TIMER0_COMPA_vect){//Scheduler
	static int sign=0;
	isrTestB0 >= SCHEDULER?sign=0:(isrTestB0 <= 0?sign=1:0);
	sign == 0?isrTestB0--:isrTestB0++;
	currentMenu=MAINMENU;
	skip=NO;
		//need for the parameter(). To be able to used the enter key twice. Otherwise, enter would change the mode at once
	changeMode=YES;
isbuttonpressed(enter)
{
	enter->state=RELEASED;
	while(1){//Need to keep control here
		(*Menu[mainMenuPointer])();
		ispressed(down->name){// The isbuttonpressed can not work. The PCINT26 is inactive here
				if(currentMenu == SUBMENU && skip==NO)
					subMenuPointer <= 0?( subMenuPointer=maxSubMenu ):subMenuPointer--;
		}
		ispressed(up->name){// The isbuttonpressed can not work. The PCINT26 is inactive here
			if(currentMenu == SUBMENU && skip==NO)
				subMenuPointer >= maxSubMenu?( subMenuPointer=0 ):subMenuPointer++;
		}
		ispressed(cancel->name)
		{ 	// The isbuttonpressed can not work. The PCINT26 is inactive here
			subMenuPointer=0;
			currentMenu=MAINMENU;
			cancel->state=RELEASED;
			//need for the parameter(). To be able to used the enter key twice. Otherwise, enter would change the mode at once
			changeMode=NO;
			mode=SELECTION;
			LCD_clear();
			break;
		}
		ispressed(enter->name){// The isbuttonpressed can not work. The PCINT26 is inactive here
			enter->state=PRESSED;
			if(currentMenu == SUBMENU && skip==NO)
				displayNumber("OK",subMenuPointer);
			if(changeMode == YES)
				mode=( mode == SELECTION )?MODIFICATION:SELECTION;
		}
		down->state=RELEASED;
		up->state=RELEASED;
		enter->state=RELEASED;
	}
}
	scheduler();
	//Wait for 1sec if nothing happens, the display the notifications
}


//Handle button presses
ISR(PCINT2_vect){
	//Reduce lcd 
	interrupt=TRUE;
	delayTime=LCD_DELAY/3;
	ispressed(up->name){
	up->state=PRESSED;
	if(currentMenu == MAINMENU ){
		mainMenuPointer >= maxMainMenu?(mainMenuPointer=0):(mainMenuPointer++);
		menu(mainMenuPointer,maxMainMenu);
	}
}
ispressed(down->name){
	down->state=PRESSED;
	if(currentMenu == MAINMENU ){
		mainMenuPointer <= 0?(mainMenuPointer=maxMainMenu):(mainMenuPointer--);
		menu(mainMenuPointer,maxMainMenu);
			}
}
ispressed(enter->name){
	enter->state=PRESSED;
	if(currentMenu == MAINMENU && skip == NO)
	displayNumber("OK",mainMenuPointer);
}
ispressed(cancel->name){
	cancel->state=PRESSED;
	displayText("Ready","");
}
delayTime=LCD_DELAY;
}


int main(){
cli();
init();
greetings();
sei();
while(1){
	changeState(s);
}
}
