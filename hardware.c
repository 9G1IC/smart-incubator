#include "hardware.h"
#include "state.h" 
#include "lcd.h" 
#include "dht22.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void	getTemperature(){
dht_read_temp(sensorData,&t->currentTemperature);
}

void	getHumidity(){
dht_read_hum(sensorData,&h->currentHumidity);
}


void ledInit(){
	LED_IO;
}


void buzzerInit(){
	BUZZER_IO;
}


void sensorInit(){
	SENSOR_IO;
	dht_init(sensorData,SENSOR_PIN);
}


void inputInit(){
	INPUT_IO;
}


void interruptInit(){
//PWM
TCCR2A =_BV(COM2A1) | _BV(COM2A1) | _BV(COM2B1) | _BV(COM2B1)| _BV(WGM20) | _BV(WGM20) ;
TCCR2B = _BV(CS20);//|_BV(WGM22)  ;
TIMSK2=0;
FAN_IO;
LIGHT_IO;
FAN_PWM=MIN;
LIGHT_PWM=MIN;
	 
//ISR
ISR_PRESCALER;
ISR_MODE_MATCH;
ISR_MODE_WGM;
ISR_FORCE;
ISR_INTERRUPT_MASK;
//Input 
INPUT_INT_CONTROL;
INPUT_INT_FLAG;
INPUT_INT_MASK;
}


void hardwareInit(){
readerClock=clkForumlar(10.0,PRESCALER);//10ms resolution
schedulerClock=clkForumlar(100.0,PRESCALER);//100ms resolution
READER=255;
SCHEDULER=255;//Ten times slower then reader
interruptInit();
sensorInit();
buzzerInit();
ledInit();
LCD_init();
inputInit();
}


void ledException(int pin,Switch state){
	switch(state){
	case ON: 
		//Turn every other bit off except pin
		clearBit(LED_PORT,pin);
	break;
	case OFF:
		//Turn every other bit off except pin
		setBit(LED_PORT,pin);
	break;
	}
}


void animate(){
}


void ledAlert(int times,int pin){
	//Pulse the leds times times
	for (int start=0;start < times; start ++){
	clearBit(LED_PORT,pin);
	_delay_msec(500);
	setBit(LED_PORT,pin);
	_delay_msec(500);
	}
	clearBit(LED_PORT,pin);
	_delay_msec(300);
}


void buzzerAlert(int times){
	//Pulse the sound times times
		setBit(BUZZER_PORT,BUZZER_PIN);
		_delay_msec(900);
		clearBit(BUZZER_PORT,BUZZER_PIN);
}



float clkForumlar(float clk,int prescaler){
	//Determine counter for precise timing; since the ISR is too fast
	//0.064ms
	float sck = F_CPU/1000;//Scale down the clock
	float scale = sck/prescaler;
	float period = 1/scale;
return clk/period;
}



void emergency(){
//This would turn off all the leds except the given on
	ledException(EMERGENCY_LED,ON);
	ledAlert(EMERGENCY_LED,5);
	//Buzz five times
	buzzerAlert(5);
}
//Function Definitions

 void chargeControl(){
	 //TODO:
	 //clear all control leds and buttons
	 //
	 //Display charging on the LCD
	showMessage('n',0);
	 blink(CHARGE_LED);
 //Checks if baby is present
	kill_switch(){
		//Yes	
	tscheduler=ON;
	}
	else
	{
		//No	
	 //Turn off scheduler
		tscheduler=OFF;
	}
}

void fanControl(){
	//Use the maxMagnitude to determine the pertage
	if(hardwareState->OnEmergency == OFF && hardwareState->OnFan == ON)
	{
		setBit(FAN_PORT,FAN_PIN);
		//Scale fan error to 255
		fanControlScaleError = ( t->percentageError->maxMagnitude / 100.0) * 255.0;
		fanControlScaleError = fanControlScaleError % 256;
		fanModulator = fanControlScaleError;
	}
	else
	if(hardwareState->OnEmergency == ON && hardwareState->OnFan == ON)
	{
		//Turn the PORT PIN for the fan on
		setBit(FAN_PORT,FAN_PIN);
		fanModulator = MAX;
	}//Full throttle
	else
	if(hardwareState->OnFan == OFF)
	{
		//Off the fans
	       	clearBit(FAN_PORT,FAN_PIN);
		fanModulator=MIN;
       	}
	FAN_PWM = fanModulator;

}

void lightControl(){
	//Use the maxMagnitude to determine the pertage
	if(hardwareState->OnEmergency == OFF && hardwareState->OnLight == ON)
	{
		
		setBit(LIGHT_PORT,LIGHT_PIN);
		//Scale light error to 255
		lightControlScaleError = ( t->percentageError->minMagnitude / 100.0) * 255.0;
		lightControlScaleError = lightControlScaleError % 256;
		lightModulator = lightControlScaleError;

	}
	else
	if(hardwareState->OnEmergency == ON  && hardwareState->OnLight == ON )
	{
		setBit(LIGHT_PORT,LIGHT_PIN);
		lightModulator = MAX;
	}//Full throttle
	else
	if(hardwareState->OnLight == OFF)
	{
		//Off the lights
	       	clearBit(LIGHT_PORT,LIGHT_PIN);
		lightModulator = MIN;
       	}

		LIGHT_PWM = lightModulator;
}
//Buttons

bool buttonCycle(_Button *b){
ispressed(b->name)
	b->state=PRESSED;
isreleased(b->name)
	b->state=RELEASED;
//Only when the button is pressed then relesed, do you trigger
if(b->state==PRESSED && b->state==RELEASED)
	return TRUE;
else
	return FALSE;
}

bool debounceButton(_Button pin,  int i ){
	bool button;
	if(i < 8){
	//Take 8 samples	
		ispressed(pin.name)
			button=TRUE;
		else
			button=FALSE;

		rawPress = INPUT_PIN & _BV(pin.name);//Extract the value of pin
		buttonBuffer|=(rawPress << i);//create a binary signature
	}
	else
			i=0;//Wrap around
	debounceResult = buttonBuffer & 0xFF;//the result must be 0xFF at steady state
	if(debounceResult == 0xFF)
		return TRUE;
	else
		return FALSE;
}
