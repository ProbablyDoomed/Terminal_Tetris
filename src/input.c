#include "input.h" 

#include <stdio.h>

#define IN_BUF_SIZE (128)

typedef struct
{
	BOOL pressed;
	WORD keybind;
} key_status_t;


static HANDLE stdIn; 
static INPUT_RECORD inputBuffer[IN_BUF_SIZE];
static DWORD unread, read;

static key_status_t keyStates[TOTAL_KEY_INPUTS] = 
{
	{.keybind = VK_UP, 		.pressed = FALSE},
	{.keybind = VK_DOWN, 	.pressed = FALSE},
	{.keybind = VK_LEFT, 	.pressed = FALSE},
	{.keybind = VK_RIGHT, 	.pressed = FALSE},
									   
	{.keybind = 0x58,		.pressed = FALSE},
	{.keybind = 0x5A,		.pressed = FALSE},
	{.keybind = 0x51,		.pressed = FALSE}
};

void input_Init()
{	
	stdIn = GetStdHandle(STD_INPUT_HANDLE);
}

BOOL input_UpdateKeyState()
{
	BOOL ret = FALSE;
	GetNumberOfConsoleInputEvents(stdIn,&unread);
	
	for(int j = 0; j < TOTAL_KEY_INPUTS; j++)
	{
		keyStates[j].pressed = FALSE;
	}
	
	if(unread != 0) 
	{
		ReadConsoleInput(stdIn, inputBuffer, IN_BUF_SIZE, &read);
		
		for (int i = 0; i < read; i++)
        {
			if(inputBuffer[i].EventType == KEY_EVENT)
			{
				KEY_EVENT_RECORD event = inputBuffer[i].Event.KeyEvent;		
				
				for(int j = 0; j < TOTAL_KEY_INPUTS; j++)
				{
					if(event.wVirtualKeyCode == keyStates[j].keybind 
						&& event.bKeyDown == TRUE)
					{
						keyStates[j].pressed = TRUE;
						ret = TRUE;
						break;
					}
				}				
			}
		}
		
	}	

	return ret;

}

BOOL input_GetKeyState(key_input_t key)
{
	return keyStates[key].pressed;
}

