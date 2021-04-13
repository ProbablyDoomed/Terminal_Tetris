
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <windows.h>

#include "draw.h"
#include "game.h"
#include "hiscore.h"
#include "input.h"
#include "blocks.h" 

int main()
{
	draw_Init();
	input_Init();
	
	uint16_t x=0,y=0;
	
	while(1)
	{
		BOOL slow = FALSE;
		if(input_UpdateKeyState())
		{
			slow = input_GetKeyState(KEY_UP);
			if(input_GetKeyState(KEY_DOWN)) y++;
			if(input_GetKeyState(KEY_LEFT)) x--;
			if(input_GetKeyState(KEY_RIGHT)) x++;			
		}
		
		if(!slow) y++;
		
		if (x < 1) x = 1;
		if (x > (SCREEN_WIDTH/2)-1) x = (SCREEN_WIDTH/2)-1;
		if (y < 0 || y >= SCREEN_HEIGHT) y = 0;
		
		draw_DrawPlayArea();
		draw_DrawBlock(x,y);
		//draw_DrawBlock(x+1,y);
		//draw_DrawBlock(x+1,y+1);
		//draw_DrawBlock(x,y+1);
		
		//if(input_GetKeyState(KEY_ACTION_1)) printf("A! ");
		//if(input_GetKeyState(KEY_ACTION_2)) printf("B! ");
		if(input_GetKeyState(KEY_BACK)) 
		{
			printf("\nGoodbye!\n");
			break;
		}
		
		usleep(200000);
	}
	
	return 0;
}