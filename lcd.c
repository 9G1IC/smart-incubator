#define F_CPU 16000000UL
#include "lcd.h"
#include "hardware.h"
#include <string.h>
#include <ctype.h>
#include "delay.h"
#include "state.h"

char * booltostring(bool data);

const char LCD_STATE[][15]={"IDLE:","COOLING","F_COOLING", "F_WARMING", "WARMING","UNKNOWN:"};
const char LCD_TEMPERATURE[][15] ={"TEMP:","MAXTEMP:","NORMTEMP:", "MINTEMP:", "MINSAFETEMP:","MAXSAFETEMP:"};
const char LCD_HUMIDITY[][15] ={"HUMID:","MAXHUMID:", "NORMHUMID:", "MINHUMID:", "MINSAFEHUM:", "MAXSAFEHUM:"};
const char LCD_NOTIFY[][15] ={ "CHARGING","WELCOME!!!", "GOODBYE!!!","EMERGENCY!!!","ERROR!!!","NO BABY!!!" };


void lcdCmdPrepare(){
clearLcd(LCD_RESET);
clearLcd(LCD_RW);
setLcd(LCD_ENABLE);
_delay_usec(waitTime);
clearLcd(LCD_ENABLE);
_delay_usec(waitTime);
}

void LCD_cmd(uint8_t cmd){
	LCD_PORT = cmd;
	lcdCmdPrepare();
}

void sendCmd(uint8_t cmd_value){
      uint8_t cmd_value1;  
      cmd_value1 = cmd_value & 0xF0;          //mask lower nibble  
                          //because PA4-PA7 pins are used.   
      LCD_cmd(cmd_value1);               // send to LCD  
      cmd_value1 = ((cmd_value<<4) & 0xF0);     //shift 4-bit and   
                                    //mask  
      LCD_cmd(cmd_value1);               // send to LCD  
}

void lcdWritePrepare(){
	setLcd(LCD_RESET);
	clearLcd(LCD_RW);
	setLcd(LCD_ENABLE);
	_delay_usec(waitTime);
	clearLcd(LCD_ENABLE);
	_delay_usec(waitTime);
}

void LCD_write(uint8_t data){
LCD_PORT = data;
lcdWritePrepare();
}

void sendByte(uint8_t data_value){
      uint8_t data_value1;  
      data_value1=data_value & 0xF0;  
      LCD_write(data_value1);  
      data_value1=((data_value<<4) & 0xF0);  
      LCD_write(data_value1);  
}

void LCD_char(uint8_t ch){
sendByte(ch);
}

void LCD_init(){
//implement delay
LCD_PORT = 0xFF;
LCD_DDR = 0xFF;//set direction register
sendCmd(0x28);		//Use two lines, 4 bit mode
_delay_usec(waitTime);
sendCmd(0x01);          // make clear LCD
_delay_usec(waitTime);
sendCmd(0x02);          // return home
_delay_usec(waitTime);
sendCmd(0x0C);          //disable cursor
_delay_usec(waitTime);
sendCmd(0x06);          // make increment in cursor
_delay_usec(waitTime);
}


void LCD_home(){
	sendCmd(0x02);
}

void LCD_clear(){
	sendCmd(CLEAR_DISPLAY);
	LCD_home();
}
void LCD_reset(){
	sendCmd(0x0A);
}
void LCD_line(uint8_t row){
	switch(row){
		case 0:
			sendCmd(0x80);
		break;
		case 1:
			sendCmd(0xC0);
		break;
	}
}

void LCD_message(const char *text){
int i=0;
while(text[i]!='\0')                               // loop will go on till the NULL character in the string
{
sendByte(text[i]);                            // sending data on LCD byte by byte
i++;
}
text="";
}

void msgTitle(const char *text){
		LCD_clear();
		LCD_home();
		LCD_line(0);
		FRAME_BUFFER_0=text;
	LCD_message(FRAME_BUFFER_0);
	FRAME_BUFFER_0="";
}

void msgBody(const char *text){
	LCD_line(1);
	FRAME_BUFFER_1=text;
	LCD_message(FRAME_BUFFER_1);
	FRAME_BUFFER_0="";
}

void LCD_interger(int data){
	char st[8] = "";
	//sprintf(st,"%d",data);
	itoa(data,st,10);
	msgBody(st);
}

char * numtostring(int data){
	char dest[8]="";
	return itoa(data,dest,10);
}

char * bintostring(int data){
	char dest[8]="";
	return itoa(data,dest,2);
}


char * hextostring(int data){
	char st[8]="";
	return itoa(data,st,16);
}
char * booltostring(bool data){
	return (data == TRUE)?"TRUE":"FALSE";
}
char * switchtostring(Switch data){
	return (data == ON)?"ON":"OFF";
}
char * buttontostring(_Button data){
	return data.state == PRESSED?"PRESSED":"RELEASED";
}
char * buttonptrtostring(_Button * data){
	return data->state == PRESSED?"PRESSED":"RELEASED";
}
char * errortostring(_ERROR *data){
    char * ret="";
ret=(data->direction == POSITIVE)?"POSITIVE":( data->direction == NEGAGTIVE )?"NEGAGTIVE":"NO_CHANGE";
return ret;
}

void displayNumber(char * title, int data){
msgTitle(title);
_delay_usec(waitTime);
msgBody(numtostring(data));
_delay_msec(delayTime);
//clear title
title="";
}

void displayText(char * title, char * data){
msgTitle(title);
msgBody(data);
_delay_msec(delayTime);
//clear title
title="";
}

void displayBin(char * title, int data){
msgTitle(title);
_delay_usec(waitTime);
msgBody(bintostring(data));
_delay_msec(delayTime);
//clear title
title="";
}

char * catDisplay(char * cat, char * src, char * title){
char dest[18]="";
strcpy(dest,"");//Clear string
strcpy(dest,cat);
strcat(dest,src);
displayText(title,dest);
strcpy(cat,dest);
//clear title
title="";
return dest;
}

char * _toLower( char * data){
char dest[15]="";
for(int i=0;i<strlen(data);i++)
dest[i]= (char)tolower(data[i]);
strcpy(data,dest);
return data;
}
char * showMessage(char m,int index){
		char * temp="";
	switch(m){
		case 'h': //Humidity
			displayText("HUMIDITY: ", LCD_HUMIDITY[index]);
		break;
		case 't'://Temperature
			displayText("TEMPERATURE: ", LCD_TEMPERATURE[index]);
		break;
		case 'n'://Notify
			displayText("NOTIFICATION: ",LCD_NOTIFY[index]);
		break;
		case 's'://State
			displayText("STATE: ",LCD_STATE[index]);
		break;
		case 'a':
			displayText("ALERT: ","Unknown");
			break;
	}
	return temp;
}
