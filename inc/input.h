#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <windows.h>

typedef enum 
{
	KEY_UP=0,	
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	
	KEY_ACTION_1,
	KEY_ACTION_2,	
	KEY_BACK,
	
	TOTAL_KEY_INPUTS
	
} key_input_t;

void input_Init();
BOOL input_UpdateKeyState();
BOOL input_GetKeyState(key_input_t key);


#endif /* INPUT_H */

