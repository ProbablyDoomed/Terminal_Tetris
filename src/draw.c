#include "draw.h" 

#include <stdio.h>
#include <windows.h>

static HANDLE stdOut; 
static COORD coords;

static void PlaceCursor(uint16_t cx, uint16_t cy);
static void ClearScreen();

void draw_Init()
{	
	stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND window = GetConsoleWindow();
	
	DWORD existingConsoleMode;
	
	GetConsoleMode(stdOut, 	&existingConsoleMode);
	
	SetConsoleMode(stdOut, 	existingConsoleMode 
							| ENABLE_VIRTUAL_TERMINAL_INPUT 
							| ENABLE_VIRTUAL_TERMINAL_PROCESSING);	
								
	ClearScreen();
	
    //RECT r;
    //GetWindowRect(window, &r);
    //MoveWindow(window, r.left, r.top, SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
	
	COORD bufferSizeCoords;
    bufferSizeCoords.X = SCREEN_WIDTH;
    bufferSizeCoords.Y = SCREEN_HEIGHT;
	
	SMALL_RECT windowRect;
    windowRect.Top = 0;
    windowRect.Left = 0;
    windowRect.Right = SCREEN_WIDTH-1;
    windowRect.Bottom = SCREEN_HEIGHT-1 ;
	
    SetConsoleScreenBufferSize(stdOut, bufferSizeCoords);
	SetConsoleWindowInfo(stdOut, TRUE, &windowRect);
}

void draw_DrawPlayArea()
{
	ClearScreen();
}

void draw_DrawScore(uint64_t score)
{
	
}

void draw_DrawBlock(uint16_t blockX, uint16_t blockY)
{
	PlaceCursor(blockX*2,blockY);
	printf("[]");
}


static void PlaceCursor(uint16_t cx, uint16_t cy)
{
	coords.X = cx;
	coords.Y = cy;
	SetConsoleCursorPosition(stdOut, coords);
}

static void ClearScreen()
{
	COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(stdOut, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(stdOut,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(stdOut, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(stdOut,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(stdOut, coordScreen);
}
