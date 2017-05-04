#include "state.h"
#include "lcd.h"
#include "hardware.h"


 void calcuatePercentageError(_ERROR * e,float averageValue, float nominalValue, float maximumValue,float minimumValue,float gain){
	 e->maxMagnitude = ( gain * fabs((averageValue - nominalValue)/(maximumValue - nominalValue)) ) * 100.0;
	 e->minMagnitude = (gain * fabs((averageValue - nominalValue)/(minimumValue - nominalValue))) * 100.0;
errorSign =( averageValue - nominalValue  )* 10;

	 if ( errorSign < 0)
		 e->direction = NEGAGTIVE;
	 else 
			if (errorSign > 0)
				e->direction = POSITIVE;
	 	else
		 if ( errorSign == 0)
		 e->direction = NO_CHANGE;
 }
//Calculate temperature error
void temperaturePercentageError(_TEMPERATURE * temp){
calcuatePercentageError(temp->percentageError,temp->averageTemperature,temp->nominalTemperature,temp->maximumSafeTemperature,temp->minimumSafeTemperature,temp->sensitivity);

}

//Calculate humidity error
void humidityPercentageError(_HUMIDITY * hum){
 calcuatePercentageError(hum->percentageError,hum->averageHumidity,hum->nominalHumidity,hum->maximumSafeHumidity ,hum->minimumSafeHumidity,hum->sensitivity);

}
//Calculate moving average
void movingAverage(_TEMPERATURE *temp,_HUMIDITY *hum){
static int counter=0;
static float _currentTemperature=0.0;
static float _currentHumidity=0.0;
if(counter < 10){
_currentTemperature += temp->currentTemperature;
_currentHumidity += hum->currentHumidity;
counter++;
}
else
if(counter >= 10)
{
	//Find average
	temp->averageTemperature =_currentTemperature/counter;
	hum->averageHumidity = _currentHumidity/counter;
	_currentHumidity=0.0;
	_currentTemperature=0.0;
	counter=0;
}
}
//States
void nextState(_STATE *s){
if (t->averageTemperature < t->minimumSafeTemperature)
		s->nextState = FAST_WARM;
	else
			if(t->averageTemperature > t->maximumSafeTemperature)
				s->nextState = FAST_COOL;
		else
				if (t->averageTemperature == t->maximumSafeTemperature || t->averageTemperature > t->nominalTemperature)
				s->nextState = COOL;
			else
					if(t->averageTemperature == t->minimumSafeTemperature || t->averageTemperature < t->nominalTemperature)
					s->nextState = WARM;
				else
						if(t->averageTemperature == t->nominalTemperature)
						s->nextState = IDLE;
					else
						s->nextState = UNKNOWN;

	/*
if (h->averageHumidity < h->minimumSafeHumidity)
		s->nextState = FAST_WARM;
	else
			if(h->averageHumidity > h->maximumSafeHumidity)
				s->nextState = FAST_COOL;
		else
				if (h->averageHumidity == h->maximumSafeHumidity || h->averageHumidity > h->nominalHumidity)
				s->nextState = COOL;
			else
					if(h->averageHumidity == h->minimumSafeHumidity || h->averageHumidity < h->nominalHumidity)
					s->nextState = WARM;
				else
						if(h->averageHumidity == h->nominalHumidity)
						s->nextState = IDLE;
					else
						s->nextState = UNKNOWN;
						*/
}
void scheduler(){
//Changes states every 200ms
nextState(s);
}

void coolState(){
	fanControl();
	lightControl();
}
void fastCoolState(){
	fanControl();
	lightControl();
}
void fastWarmState(){
	fanControl();
	lightControl();
}
void warmState(){
	fanControl();
	lightControl();
}
void idleState(){
	fanControl();
	lightControl();
}

void  	toCoolState(){
hardwareState->OnFan=ON;
	//The heat does not necessarily have to be off
hardwareState->OnLight=OFF;
hardwareState->OnEmergency=OFF;
coolState();
}
 void 	toFastCoolState(){
hardwareState->OnFan=ON;
	 //The heat must be off
hardwareState->OnLight=OFF;
hardwareState->OnEmergency=ON;
fastCoolState();
 }
 void 	toWarmState(){
	 //The fan does not necessarily have to be off
hardwareState->OnFan=OFF;
hardwareState->OnLight=ON;
hardwareState->OnEmergency=OFF;
warmState();
 }
 void 	toFastWarmState(){
	 //The fan must be off
hardwareState->OnFan=OFF;
hardwareState->OnLight=ON;
hardwareState->OnEmergency=ON;
fastWarmState();
 }
 void	toIdleState(){
	 //All is well
hardwareState->OnFan=OFF;
hardwareState->OnLight=OFF;
hardwareState->OnEmergency=OFF;
idleState();
 }
void toUnknownState(){
	toIdleState();
}

void changeState(_STATE *s){
	//Determine error
	humidityPercentageError(h);
	temperaturePercentageError(t);
switch(s->nextState){
	case COOL:
		toCoolState();
		s->currentState=COOL;
	break;
	case WARM:
		toWarmState();
		s->currentState=WARM;
	break;
	case FAST_COOL:
		toFastCoolState();
		s->currentState=FAST_COOL;
		emergency();
	break;
	case FAST_WARM:
		toFastWarmState();
		s->currentState=FAST_WARM;
		emergency();
	break;
	case IDLE:
		toIdleState();
		s->currentState=IDLE;
	break;
	default:
		toUnknownState();
		s->currentState=UNKNOWN;
}
}

void notifictions(){
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
