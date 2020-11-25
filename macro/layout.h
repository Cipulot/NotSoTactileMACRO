#include "HID-Settings.h"

//Declaring inputs and outputs
//also we retreive count for matrix init
byte inputs[] = {6, 7, 8};
#define inCount sizeof(inputs) / sizeof(inputs[0])
byte outputs[] = {2, 3, 4, 5};
#define outCount sizeof(outputs) / sizeof(outputs[0])

//Matrix containing chars that will be used by Keyboard
//layout[macro layer no. X][row][column]
char layout[4][outCount][inCount] = {
    {{'0', '0', '.'},
     {'7', '8', '9'},
     {'4', '5', '6'},
     {'1', '2', '3'}},
    {{'a', 'b', 'c'},
     {'d', 'e', 'f'},
     {'g', 'h', 'i'},
     {'z', 'z', 'z'}},
    {{'!', '@', '#'},
     {'$', '%', '^'},
     {'&', '*', '('},
     {')', '-', '='}},
    {{';', '/', '.'},
     {'?', '|', '9'},
     {'4', '5', '6'},
     {'1', '2', '3'}}};

//Matrix for rotary encoder codes that will be executed by Consumer
//rotary[encoder no. X][macro layer no. Y][rotation x, rotation y, button press]
uint16_t rotary[2][4][3] = {
    {{MEDIA_VOLUME_DOWN, MEDIA_VOLUME_UP, MEDIA_PLAY_PAUSE},
     {0x00, 0x00, 0x00},
     {0x00, 0x00, 0x00},
     {0x00, 0x00, 0x00}},
    {{MEDIA_NEXT, MEDIA_PREVIOUS, 0x00},
     {0x00, 0x00, 0x00},
     {0x00, 0x00, 0x00},
     {0x00, 0x00, 0x00}}};

int keyDown[4][outCount][inCount];
bool keyLong[4][outCount][inCount];
int layoutSelect = 0;

//Just and example for language switching in windows
/*
Keyboard.press(KEY_LEFT_SHIFT);
Keyboard.press(KEY_LEFT_CTRL);
Keyboard.releaseAll();
*/