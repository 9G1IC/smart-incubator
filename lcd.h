#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#define LCD_DELAY 600
//Macros
#ifndef LCD_PORT
#define LCD_PORT 	PORTC
#endif

#ifndef LCD_DDR
#define LCD_DDR		DDRC
#endif

#ifndef setBit
#define setBit(x,y) x |= _BV(y)
#endif

#ifndef clearBit
#define clearBit(x,y) x &= ~_BV(y)
#endif

#ifndef setLcd
#define setLcd(bit) setBit(LCD_PORT,bit)
#endif
#ifndef clearLcd
#define clearLcd(bit) clearBit(LCD_PORT,bit)
#endif

#define LCD_ENABLE	0	
#define LCD_RW		1
#define LCD_RESET 	2

#define CLEAR_DISPLAY    0x01
#define SET_CURSOR       0x80
//Routines


//This enables us to use interrupts to write to LCD
char *FRAME_BUFFER_0;
char *FRAME_BUFFER_1;
char * _toLower( char * data);
char * bintostring(int data);
//char * booltostring(bool data);
char * buttontostring(_Button);
char * catDisplay(char * cat, char * src, char * title);
//char * errortostring(_ERROR *data);
char * hextostring(int data);
char * numtostring(int data);
char * showMessage(char m,int index);
//char * switchtostring(_HARDWARE_STATE data);
void LCD_char(uint8_t ch);
void LCD_clear();
void LCD_cmd(uint8_t cmd);
void LCD_hex(int data);
void LCD_home();
void LCD_init();
void LCD_interger(int data);
void LCD_line(uint8_t row);
void LCD_message(const char *text);
void LCD_write(uint8_t data);
void displayBin(char * title, int data);
void displayNumber(char * title, int data);
void displayText(char * title, char * data);
void lcdCmdPrepare();
void lcdWritePrepare();
void msgBody(const char *text);
void msgTitle(const char *text);
void sendByte(uint8_t data_value);
void sendCmd(uint8_t cmd_value);

int waitTime;
int delayTime;
