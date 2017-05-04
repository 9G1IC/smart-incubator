#include "types.h"
#define F_CPU 16000000UL
//Menu Limit
#define MAX 255
#define MIN 0
//Timer interupts
#define test
#define _8
#ifndef test
#define PRESCALER 1024
#define ISR_PRESCALER 			TCCR0B |= _BV(CS01) | _BV(CS00) //Set prescaler to / 1024
#define COM_SET  			_BV(COM0A1) //Set to clear on match
#endif
#ifdef test
#ifdef _NONE
#define ISR_PRESCALER 			TCCR0B |= _BV(CS00) //Set prescaler None
#define PRESCALER 1
#endif
#ifdef _8 
#define ISR_PRESCALER 			TCCR0B |= _BV(CS01) //Set prescaler to / 8
#define PRESCALER 8
#endif
#ifdef _64 
#define ISR_PRESCALER 			TCCR0B |= _BV(CS01) | _BV(CS00) //Set prescaler to / 64
#define PRESCALER 64
#endif
#ifdef _256 
#define ISR_PRESCALER 			TCCR0B |= BV(CS02) //Set prescaler 256
#define PRESCALER 256
#endif
#ifdef _1024
#define ISR_PRESCALER 			TCCR0B |= _BV(CS02) | _BV(CS00) //Set prescaler to / 1024
#define PRESCALER 1024 
#endif
#endif//End begin
//Set CTC
#define COM_SET_A  			_BV(COM0A1) | _BV(COM0A0)//Set to clear on match
#define COM_SET_B  			_BV(COM0B1) | _BV(COM0B0)//Set to clear on match
#define ISR_INTERRUPT_MASK 		TIMSK0|=_BV(OCIE0B) | _BV(OCIE0A)
#define ISR_MODE_MATCH 			TCCR0A |= COM_SET_A | COM_SET_B
#define ISR_MODE_WGM 			TCCR0A|=_BV(WGM01)//set CTC
#define ISR_FORCE			TCCR0B|=_BV(FOC0A) | _BV(FOC0B)
//Define the registers
#define READER				OCR0B //PB7 PWMH13
#define SCHEDULER  			OCR0A //PG5 PWML4
#ifdef COM_SET_A
#undef COM_SET_A
#endif
#ifdef COM_SET_B
#undef COM_SET_B
#endif
//PWM Interrupt
//Redefine com_set and set mode
#define COM_SET_A  			_BV(COM2A1) | _BV(COM2A0)//Set to clear on match
#define COM_SET_B  			_BV(COM2B1) | _BV(COM2B1)//Set to clear on match
#define PWM_MODE_MATCH 			TCCR2A |= COM_SET_B | COM_SET_A
#define PWM_MODE_WGM_A 	TCCR2A|=_BV(WGM20)|_BV(WGM20)
#define PWM_MODE_WGM_B 	TCCR2B|=_BV(WGM22)
#define PWM_PRESCALER			TCCR2B |=  _BV(CS20)//Set prescaler to / 8 and phase correct PWM
//Define the registers
#define FAN_PORT 			PORTB
#define FAN_DDR				DDRB

#ifdef test
#define FAN_PIN 			PB4//OC2A on atmega2560
#else
#define FAN_PIN 			PB3//OC2A on atmega168
#endif

#define FAN_IO				FAN_DDR|=_BV(FAN_PIN);FAN_PORT |=_BV(FAN_PIN)//Set pin to output
#define FAN_PWM 			OCR2A //PB4 PWMH10
#ifdef test
#define LIGHT_PIN 			PH6
#define	LIGHT_DDR			DDRH
#define LIGHT_PORT 			PORTH
#else
#define LIGHT_PIN 			PD3
#define	LIGHT_DDR			DDRD
#define LIGHT_PORT 			PORTD
#endif
#define LIGHT_IO			LIGHT_DDR|=_BV(LIGHT_PIN);LIGHT_PORT|=_BV(LIGHT_PIN)//Set pin to output
#define LIGHT_PWM 			OCR2B //PH6 PWMH9
#define BUZZER_PORT 	PORTB
#define BUZZER_DDR	DDRB
#define BUZZER_PIN      PB1
#define BUZZER_IO 	BUZZER_DDR|=_BV(BUZZER_PIN);BUZZER_PORT|=_BV( BUZZER_PIN)//Set pin to output
#define	SENSOR_PORT	PORTB
#define	SENSOR_DDR	DDRB
#define SENSOR_PINB 	PINB
#define SENSOR_PIN 	PB0
#define SENSOR_IO 	SENSOR_DDR|=~_BV(SENSOR_PIN);SENSOR_PORT|=_BV( SENSOR_PIN)//Set pin to input

#define	EMERGENCY_LED	PB5
#define	NOMINAL_LED	PB2

#ifdef test
#define	COOL_LED	PB6  //Free on all (atmega168 and atmega2560)
#define LED_MASK	0xEE//11101110
#else
#define	COOL_LED	PB4 //Used for OC2A on atmega2560 
#define LED_MASK	0xE6//11100110
#endif

#define	WARM_LED	PB5 
#define CHARGE_LED	PB6 //Formerly PB6
#define LED_PORT 	PORTB
#define LED_DDR		DDRB
#define LED_IO 		LED_PORT|=LED_MASK;LED_DDR|=LED_MASK
//PCINT interrupts
//TODO://Make buttons interrupts: PCINT16 PCINT17 PCINT18 PCINT20
#define INPUT_INT_CONTROL 	PCICR |= _BV(PCIE2) //Enable PCINT23-16
#define INPUT_INT_FLAG 		PCIFR |= _BV(PCIF2)
#define INPUT_INT_MASK 		PCMSK2 |= _BV(PCINT16) | _BV(PCINT17) | _BV(PCINT18) | _BV(PCINT20) | _BV(PCINT23) 
#ifdef test
#define INPUT_PORT 	PORTK
#define INPUT_DDR	DDRK
#define INPUT_PIN 	PINK
#define INPUT_MASK	0x68//01101000	
#define INPUT_IO 	INPUT_DDR=INPUT_MASK;INPUT_PORT=~INPUT_MASK
#define	ENTER_BUTTON	PINK0 //pin 17 on atmega2560	
#define	UP_BUTTON	PINK1 //pin 20 on atmega2560	
#define	DOWN_BUTTON	PINK2 //pin 19 on atmega2560	
#define KILL_SWITCH 	PINK4 //pin 21 on atmega2560	
#define CANCEL_BUTTON	PINK7 
#else
#define INPUT_PORT 	PORTD
#define INPUT_DDR	DDRD
#define INPUT_PIN 	PIND
#define INPUT_MASK	0x68//01101000	
#define INPUT_IO 	INPUT_DDR=INPUT_MASK;INPUT_PORT=~INPUT_MASK
#define KILL_SWITCH 	PIND0 //pin 21 on atmega2560	
#define	UP_BUTTON	PIND1 //pin 20 on atmega2560	
#define	DOWN_BUTTON	PIND2 //pin 19 on atmega2560	
#define	ENTER_BUTTON	PIND4 //pin 17 on atmega2560	
#define CANCEL_BUTTON	PIND7 
#endif
//Macros
#ifndef setBit
#define setBit(x,y) x|=_BV(y)
#endif
#ifndef clearBit
#define clearBit(x,y) x&=~_BV(y)
#endif
//LED
#define onled(led) setBit(LED_PORT,led)
#define blink(led) LED_PORT ^= _BV(led); _delay_msec(500)//blinks an led
//Buttons
#define whilepressed(pin) while(!(INPUT_PIN & _BV(pin)))
#define ispressed(pin) if(!(INPUT_PIN & _BV(pin)))
#define isbuttonpressed(button) if(button->state==PRESSED)
#define isbuttonreleased(button) if(button->state==RELEASED)
#define whilebuttonreleased(button) while((button->state==RELEASED))
#define whilebuttonpressed(button) while((button->state==PRESSED))
#define whilereleased(pin) while((INPUT_PIN & _BV(pin)))
#define isreleased(pin) if((INPUT_PIN & _BV(pin)))
#define init_in_pin(pin) INPUT_DDR &= ~_BV(pin); INPUT_PORT |=_BV(pin)
//Switch
#define kill_switch() ispressed(KILL_SWITCH)
struct dht22 * sensorData;
typedef enum {ON,OFF} Switch ;
typedef struct {
Switch OnFan;//Used to turn on or off the fan
Switch OnHeat;
Switch OnLight;
Switch OnEmergency;
Switch OnKillSwitch;
}_HARDWARE_STATE;
_HARDWARE_STATE * hardwareState;
typedef enum {PRESSED,RELEASED}_buttonState;
typedef struct {
_buttonState state;
int name;
}_Button;
_Button *up;
_Button *down;
_Button *enter;
_Button *cancel;
volatile Switch  tscheduler;
void lightControl();
void fanControl();
void chargeControl();
void emergency();
void buzzerAlert(int times);
void ledAlert(int times,int pin);
void animate();
void ledException(int pin,Switch state);
//Initializations
void hardwareInit();
void interruptInit();
void inputInit();
void sensorInit();
void buzzerInit();
void ledInit();
//Sensors
void	getHumidity();
void	getTemperature();
bool buttonCycle(_Button *);
float clkForumlar(float,int);
float readerClock;
float schedulerClock;
int isr_timer;
int isr_counter;
//Button variables
bool debounceButton(_Button,int);
bool buttonInterrupt;
bool  interrupt;
int buttonBuffer;
int debounceResult;
int rawPress;
int lightModulator;
int lightControlScaleError;
int fanModulator;
int fanControlScaleError;
