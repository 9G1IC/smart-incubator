#include <math.h>
#include "lcd.h"
#include "init.h"
#include "delay.h"
#include "dht22.h"
#include "hardware.h"
#include "test.h"
#include "state.h"
#include <ctype.h>
#include <avr/pgmspace.h>
	
//PUBLIC

void states(){
	currentMenu=SUBMENU;
switch(s->currentState){
	case COOL:
		showMessage('s',1);
	break;
	case WARM:
		showMessage('s',4);
	break;
	case FAST_COOL:
		showMessage('s',2);
	break;
	case FAST_WARM:
		showMessage('s',3);
	break;
	case IDLE:
		showMessage('s',0);
	break;
	default:
		showMessage('s',5);
}
}

void hardwareStateTest(){
	char *dest="";

	maxSubMenu=5;
	
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayNumber("FAN_PWM: ",FAN_PWM);
			break;
		case 1:
			displayNumber("LIGHT_PWM: ",LIGHT_PWM);
			break;
		case 2:
			displayText("Fan: ",switchtostring(hardwareState->OnFan));
			break;
		case 3:
			displayText("Heat: ",switchtostring(hardwareState->OnHeat));
			break;
		case 4:
			displayText("Light: ",switchtostring(hardwareState->OnLight));
			break;
		case 5:
			displayText("Emergency: ",switchtostring(hardwareState->OnEmergency));
			break;
		case 6:
			displayText("Kill_Switch: ",switchtostring(hardwareState->OnKillSwitch));
			break;
	}
}

void time(){
	maxSubMenu=3;
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayNumber("TIMER: ",isr_timer);
			break;
		case 1:
			displayNumber("PRESCALER: ",PRESCALER);
			break;
		case 2:
			displayNumber("READER CLK: ",ceil(readerClock));
			break;
		case 3:
			displayNumber("SCHED. CLK: ",ceil(schedulerClock));
			break;
	}
}

void settings(){
	maxSubMenu=9;
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayNumber("Max. Temp: ",t->maximumSafeTemperature*100);
			break;
		case 1:
			displayNumber("Min. Temp: ",t->minimumSafeTemperature*100);
			break;
		case 2:
			displayNumber("Norm. Temp: ",t->nominalTemperature*100);
			break;
		case 3:
			displayNumber("Avg. Temp: ",t->averageTemperature*100);
			break;
		case 4:
			displayNumber("Temp_Gain: ",t->sensitivity);
			break;
		case 5:
			displayNumber("Max. Hum: ",h->maximumSafeHumidity);
			break;
		case 6:
			displayNumber("Min. Hum: ",h->minimumSafeHumidity);
			break;
		case 7:
			displayNumber("Norm. Hum: ",h->nominalHumidity);
			break;
		case 8:
			displayNumber("Avg. Hum: ",h->averageHumidity);
			break;
		case 9:
			displayNumber("Hum_Gain: ",h->sensitivity);
			break;
	}
}

void currentValues(){
	maxSubMenu=9;
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayNumber("CURR. TEMP",t->currentTemperature*100);
			break;
		case 1:
			displayNumber("AVG. TEMP",t->averageTemperature*100);
			break;
		case 2:
			displayNumber("TEMP_MIN_ERROR:",t->percentageError->minMagnitude);
			break;
		case 3:
			displayNumber("TEMP_MAX_ERROR:",t->percentageError->maxMagnitude);
			break;
		case 4:
			displayText("TEMP.ERR. DIR",errortostring(t->percentageError));
			displayNumber("TEMP.ERR. SIGN",errorSign);
			break;
		case 5:
			displayNumber("CURR. HUM",h->currentHumidity*100);
			break;
		case 6:
			displayNumber("AVG. HUM",h->averageHumidity*100);
			break;
		case 7:
			displayNumber("HUM_MIN_ERROR:",h->percentageError->minMagnitude);
			break;
		case 8:
			displayNumber("HUM_MAX_ERROR: ",h->percentageError->maxMagnitude );
			break;
		case 9:
			displayText("HUM.ERR. DIR",errortostring(h->percentageError ));
			displayNumber("HUM.ERR. SIGN",errorSign);
			break;
	}
}

void buttonTest(){
 displayText("WARNING","press all buttons");
		ispressed(enter->name) {
			displayText("BUTTON TEST","ENTER");
		}
		ispressed(up->name){
			displayText("BUTTON TEST","UP");
		}
		ispressed(down->name){
			displayText("BUTTON TEST","DOWN");
		}
		ispressed(cancel->name){
			displayText("BUTTON TEST","CANCEL");
		}
}

void bounceDebounce(){
	
		char cat[8];
		strcpy(cat,"");//Clear
		strcat(cat,numtostring(rawPress));
		strcat(cat," : ");
		strcat(cat,numtostring(buttonBuffer));
		strcat(cat," : ");
		strcat(cat,numtostring(debounceResult));
		//Debounce:Bounce:Postion
		displayText("RAW:BUFF:RES",cat);	
}
void ledTest(){
	maxSubMenu=4;
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayText("LED_TEST","EMERG_LED");
			ledAlert(3,EMERGENCY_LED);
			break;
		case 1:
			displayText("LED_TEST","NOMIN_LED");
			ledAlert(3,NOMINAL_LED);
			break;
		case 2:
			displayText("LED_TEST","COOL_LED");
			ledAlert(3,COOL_LED);
			break;
		case 3:
			displayText("LED_TEST","WARM_LED");
			ledAlert(3,WARM_LED);
			break;
		case 4:
			displayText("LED_TEST","CHARGE_LED");
			ledAlert(3,CHARGE_LED);
			break;
	}
}

void isrTest(){

	maxSubMenu=13;
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayNumber("ISR_0_A",isrTestA0);
			break;
		case 1:
			displayNumber("ISR_0_B",isrTestB0);
			break;
		case 2:
			displayNumber("READER",READER);
			break;
		case 3:
			displayNumber("SCHEDULER",SCHEDULER);
			break;
		case 4:
			displayNumber("TCNT0",TCNT0);
			break;
		case 5:
			displayBin("TCCR0B",TCCR0B);
			break;
		case 6:
			displayBin("TCCR0A",TCCR0A);
			break;
		case 7:
			displayBin("TIFR0",TIFR0);
			break;
		case 8:
			displayBin("TIMSK0",TIMSK0);
			break;
			//PWM
		case 9:
			displayNumber("TCNT2",TCNT2);
			break;
		case 10:
			displayNumber("OCR2A",FAN_PWM);
			break;
		case 11:
			displayNumber("OCR2B",LIGHT_PWM);
			break;
		case 12:
			displayBin("TCCR2B",TCCR2B);
			break;
		case 13:
			displayBin("TCCR2A",TCCR2A);
			break;
	}
}

void modulators(){
	maxSubMenu=5;
	currentMenu=SUBMENU;
	switch(subMenuPointer){
		case 0:
			displayNumber("FAN_PWM.",FAN_PWM);
			break;
		case 1:
			displayNumber("FAN_MOD: ",fanModulator);
			break;
		case 2:
			displayNumber("FAN_S->ERROR:",fanControlScaleError);
			break;
		case 3:
			displayNumber("LIGHT_PWM.",LIGHT_PWM);
			break;
		case 4:
			displayNumber("LIGHT_MOD: ",lightModulator);
			break;
		case 5:
			displayNumber("LIGHT_S->ERROR: ",lightControlScaleError);
			break;
	}
}
char  *MAIN_MENU_LIST[18] ={ "SETTINGS","BUTTONS","TIME","STATES","HARDWARE","DEBOUNCE","LED","ISR","MODULATORS","CURRENT_VALUES","PARAM. MENU","SIMULATE"}; 


char  *parameterName[18] ={ "MIN_TEMP.","MAX_TEMP","NORM_TEMP","CURR_TEMP","AVG_TEMP","TEMP_SENSE","T%_ERR_MAX","T%_ERR_MIN","MIN_HUM","MAX_HUM","NORM_HUM","CURR_HUM","AVG_HUM","HUM_SENSE","H%_ERR_MAX","H%_ERR_MIN","LCD_DELAY","LCD_WAIT" }; 


void menu(int item,int maxSize){
	static int nextitem=0;
	char title[18]="> ";
	char body[18]="";
 char  **menuList;
		
	if(currentMenu == MAINMENU)
		menuList = MAIN_MENU_LIST;
	else
		menuList = parameterName;
	//Add > to current menu
	strcat(title,menuList[item]);
	//Wrap around
	nextitem=(nextitem >= maxSize-1)?0:item+1;
	
	//Fetch next item
	strcpy(body,menuList[nextitem]);
	_toLower(body);
	displayText(title,body);//Display item in title and nextitem in body
}
void simulate(){
	static int i=0;
	i=counter();
	FAN_PWM=i;
	LIGHT_PWM=i;
	displayNumber("Counter",i);
	ispressed(cancel->name){
		FAN_PWM=0;
		LIGHT_PWM=0;
		cancel->state=RELEASED;
	}

}
//
//This function is used to modify parameters
void parameterMenu(){
	float * param;
	static float  newParam=0.0;
	//Enter submenu
	maxSubMenu=17;
	currentMenu=SUBMENU;
switch(mode){
	case SELECTION :
	menu(subMenuPointer,maxSubMenu);
	//Set newParam only once
	param = *(parameters + subMenuPointer);
		newParam = *param;
	break;
	case MODIFICATION:
	ispressed(up->name){
		skip=YES;
		newParam+=0.1;
		//Display changed values
		displayNumber(parameterName[subMenuPointer],newParam * 10);
		up->state=RELEASED;
		changeMode=NO;
	}
	ispressed(down->name){
		skip=YES;
		newParam-=0.1;
		//Display changed values
		displayNumber(parameterName[subMenuPointer],newParam * 10);
		down->state=RELEASED;
		changeMode=NO;
	}
	ispressed(enter->name){
	//isbuttonpressed(enter){
		skip=YES;
		//Save new value of param
		**(parameters+subMenuPointer)=newParam;
		displayNumber("Saved!!",**(parameters+subMenuPointer) * 10);
		enter->state=RELEASED;
	}
	break;
}
}
void reset(){
	FAN_PWM=0;
	LIGHT_PWM=0;
	t->percentageError->maxMagnitude=0;
	t->percentageError->minMagnitude=0;
	h->percentageError->maxMagnitude=0;
	h->percentageError->maxMagnitude=0;
}

void greetings(){
displayText("->>!WELCOME!<<-","");
_delay_msec(500);
displayText("   -ADAPTIVE-   ","  >>INCUBATOR   ");
_delay_msec(500);
msgTitle("Press UP or DOWN");
msgBody("to Navigate MENU");
_delay_msec(2000);
}

int counter(){
static int tdir=0;
static int hdir=0;
static int dir=0;
static float i=0.0;
float scale=1.0;
float margin=0;
dir=(i>=MAX-1)?0:(i<=0)?1:dir;
dir==0?( i-=scale ):( i+=scale );
tdir = (t->currentTemperature > t->maximumSafeTemperature - margin)?0:(t->currentTemperature < t->minimumSafeTemperature + margin?1:tdir);

( tdir==0 )?( t->currentTemperature-(i/scale) ):(t->currentTemperature+(i/scale));
hdir = (h->currentHumidity > h->maximumSafeHumidity - margin)?0:(h->currentHumidity < h->minimumSafeHumidity + margin?1:hdir);
( hdir==0 )?( h->currentHumidity+(i/scale)):(h->currentHumidity+(i/scale));
return i;
}

