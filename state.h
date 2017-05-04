#include <avr/io.h>
#include <math.h>
 typedef struct errorParameters{
	enum _direction{POSITIVE,NEGAGTIVE,NO_CHANGE}direction;
	float minMagnitude;
	float maxMagnitude;
}_ERROR;

 typedef struct {
	float averageTemperature;
	float minimumSafeTemperature;
	float maximumSafeTemperature;
	float  nominalTemperature;
	_ERROR * percentageError;
	float sensitivity; 
	float currentTemperature;
}_TEMPERATURE;
 typedef struct {
	float averageHumidity;
	float  minimumSafeHumidity;
	float  maximumSafeHumidity;
	float  nominalHumidity;
	_ERROR * percentageError;
	float sensitivity; 
	float  currentHumidity;
}_HUMIDITY;
 typedef struct {
	enum states{
	IDLE,WARM,COOL,FAST_WARM,FAST_COOL,UNKNOWN
} currentState,nextState;
}_STATE;

float errorSign;
 _TEMPERATURE *t;
 _STATE  *s;
 _HUMIDITY  *h;
void temperaturePercentageError(_TEMPERATURE*);
 //States
void  	coolState();
void	unknownState ();
void	warmState();
void 	fastCoolState();
void 	fastWarmState();
void	idleState();
//Transistion
void  	toCoolState();
void	toUnknownState();
void 	toWarmState();
void 	tofastCoolState();
void 	tofastWarmState();
void	toidleState();
void changeState (_STATE *);
void nextState(_STATE *);//Used to determine the next state to change to
void movingAverage();
void modifyHumidity(float );
void modifyTemperature(float );
void scheduler();
