#include "state.h"
#include "hardware.h"
#include "lcd.h"
#include "dht22.h"
#include<stdlib.h>
#include "init.h"
#include "test.h"

void init(){
	//Create space for temp and hum structures
	h=malloc(sizeof(_HUMIDITY));
	s=malloc(sizeof(_STATE));
	t=malloc(sizeof(_TEMPERATURE));
	t->percentageError=malloc(sizeof(_ERROR));
	h->percentageError=malloc(sizeof(_ERROR));
	hardwareState = malloc(sizeof(_HARDWARE_STATE));
	
	//Interrupts
const float defaultMinimumSafeTemperature = 34.0;
const float defaultMaximumSafeTemperature = 38.0;
const float defaultNorminalTemperature = 36.0;
const float defaultMinimumSafeHumidity = 34.0;
const float defaultMaximumSafeHumidity = 38.0;
const float defaultNorminalHumidity = 36.0;

	//Set temperatures
	t->minimumSafeTemperature = defaultMinimumSafeTemperature;
	t->maximumSafeTemperature = defaultMaximumSafeTemperature;
	t->nominalTemperature = defaultNorminalTemperature;
	t->currentTemperature=36.0;
	t->averageTemperature=36.0;
	t->sensitivity = 1.0;
	t->percentageError->maxMagnitude=0;
	t->percentageError->direction=NO_CHANGE;
	//Set default humidity
	h->minimumSafeHumidity = defaultMinimumSafeHumidity;
	h->maximumSafeHumidity = defaultMaximumSafeHumidity;
	h->nominalHumidity=  defaultNorminalHumidity;
	h->currentHumidity=36.0;
	h->averageHumidity=36.0;
	h->sensitivity = 1.0;
	h->percentageError->maxMagnitude=0;
	h->percentageError->direction=NO_CHANGE;

//Hardware states
	hardwareState->OnLight=OFF;
	hardwareState->OnHeat=OFF;
	hardwareState->OnFan=OFF;
	hardwareState->OnEmergency=OFF;
	hardwareState->OnKillSwitch=OFF;
//
Menu[SETTINGS]=&settings;
Menu[BUTTONS]=&buttonTest;
Menu[TIME]=&time;
Menu[STATES]=&states;
Menu[HARDWARE]=&hardwareStateTest;
Menu[DEBOUNCE]=&bounceDebounce;
Menu[LED]=&ledTest;
Menu[ISR]=&isrTest;
Menu[MODULATORS]=&modulators;
Menu[CURRENTVALUES]=&currentValues;
Menu[PARAMETERMENU]=&parameterMenu;
Menu[SIMULATE]=&simulate;

parameters[0]=&t->minimumSafeTemperature;
parameters[1]=&t->maximumSafeTemperature;
parameters[2]=&t->nominalTemperature;
parameters[3]=&t->currentTemperature;
parameters[4]=&t->averageTemperature;
parameters[5]=&t->sensitivity;
parameters[6]=&t->percentageError->maxMagnitude;
parameters[7]=&t->percentageError->minMagnitude;
parameters[8]=&h->minimumSafeHumidity;
parameters[9]=&h->maximumSafeHumidity;
parameters[10]=&h->nominalHumidity;
parameters[11]=&h->currentHumidity;
parameters[12]=&h->averageHumidity;
parameters[13]=&h->sensitivity;
parameters[14]=&h->percentageError->maxMagnitude;
parameters[15]=&h->percentageError->minMagnitude;
parameters[16]=&delayTime;
parameters[17]=&waitTime;
	//LCD Times
waitTime=40;
delayTime=LCD_DELAY;
timer=0.000;


//Menu
maxMainMenu=MAX_MENU - 1;
maxSubMenu=MAX_SUB_MENU - 1;
currentMenu=MAINMENU;
FRAME_BUFFER_0=malloc(sizeof(char*));
FRAME_BUFFER_1=malloc(sizeof(char*));
skip=NO;
mode=SELECTION;
changeMode=YES;
mainMenuPointer=0;

//Buttons
enter=malloc (sizeof(_Button));
down=malloc (sizeof(_Button));
up=malloc (sizeof(_Button));
cancel=malloc (sizeof(_Button));
up->name=UP_BUTTON;
up->state=RELEASED;
down->name=DOWN_BUTTON;
down->state=RELEASED;
enter->name=ENTER_BUTTON;
enter->state=RELEASED;
cancel->name=CANCEL_BUTTON;
cancel->state=RELEASED;

interrupt=FALSE;
hardwareInit();
buzzerAlert(2);
}
