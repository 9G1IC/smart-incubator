#include <avr/pgmspace.h>
int isrTestA0;
int isrTestB0;
int isrTestA2;
int isrTestB2;
static int debounce=0;
static int bounce=0;
static int pos=0;
float timer;

char * catDisplay(char * cat, char * src, char * title);
char * numtostring(int data);
void displayNumber(char * title, int data);
void displayText(char * title, char * data);
void bounceDebounce();
void buttonTest();
void hardwareStateTest();
void isrTest();
void ledTest();
void mainTest();
void settings();
void states();
void time();
void greetings();
void modulators();
void currentValues();
void simulate();

#define MAX_MENU 12
#define MAX_SUB_MENU 18 



void (*Menu[MAX_MENU])(void);
//Menu=(void*)malloc(sizeof(void(*[12])(void)));
void parameterMenu();
void menu(int,int);
enum _MENU{MAINMENU,SUBMENU}currentMenu;
enum _MODE{SELECTION, MODIFICATION}mode;
enum _MENU_DIRECTION{UP,DOWN}menuWrap;
int maxMainMenu;
int maxSubMenu;
int mainMenuPointer;
int subMenuPointer;

float * parameters[17];
enum list {SETTINGS=0,BUTTONS,TIME,STATES,HARDWARE,DEBOUNCE,LED,ISR,MODULATORS,CURRENTVALUES,PARAMETERMENU,SIMULATE};
enum {NO=0,YES}skip,changeMode;

