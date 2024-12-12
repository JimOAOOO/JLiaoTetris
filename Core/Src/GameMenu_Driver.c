

#include "GameMenu_Driver.h"

// Variable to hold touch screen data
static STMPE811_TouchData StaticTouchData;

// Displays a string on the LCD screen at specified coordinates
void DisplayString(uint16_t x, uint16_t y, char *str) {
    while(*str) {
        LCD_DisplayChar(x, y, *str++);
        x += Font16x24.Width;  // Move x coordinate by character width for next character
    }
}

// Function to select game mode by touching screen regions
bool Game_Select(void){
	LCD_Clear(0,LCD_COLOR_WHITE);  // Clear the LCD display
	LCD_SetTextColor(LCD_COLOR_BLACK);  // Set text color to black
	LCD_SetFont(&Font16x24);  // Set font size

	// Print out all 7 blocks
	// I block
	LCD_Draw_Rectangle_Fill(1*15,1*15,15,15,COLOR_CYAN);
	LCD_Draw_Rectangle_Fill(1*15,2*15,15,15,COLOR_CYAN);
	LCD_Draw_Rectangle_Fill(1*15,3*15,15,15,COLOR_CYAN);
	LCD_Draw_Rectangle_Fill(1*15,4*15,15,15,COLOR_CYAN);
	// J block
	LCD_Draw_Rectangle_Fill(2*15,6*15,15,15,COLOR_BLUE);
	LCD_Draw_Rectangle_Fill(2*15,7*15,15,15,COLOR_BLUE);
	LCD_Draw_Rectangle_Fill(3*15,7*15,15,15,COLOR_BLUE);
	LCD_Draw_Rectangle_Fill(4*15,7*15,15,15,COLOR_BLUE);
	// L block
	LCD_Draw_Rectangle_Fill(7*15,10*15,15,15,COLOR_ORANGE);
	LCD_Draw_Rectangle_Fill(8*15,10*15,15,15,COLOR_ORANGE);
	LCD_Draw_Rectangle_Fill(9*15,10*15,15,15,COLOR_ORANGE);
	LCD_Draw_Rectangle_Fill(9*15,9*15,15,15,COLOR_ORANGE);
	// O block
	LCD_Draw_Rectangle_Fill(8*15,18*15,15,15,COLOR_YELLOW);
	LCD_Draw_Rectangle_Fill(8*15,19*15,15,15,COLOR_YELLOW);
	LCD_Draw_Rectangle_Fill(9*15,18*15,15,15,COLOR_YELLOW);
	LCD_Draw_Rectangle_Fill(9*15,19*15,15,15,COLOR_YELLOW);
	// S block
	LCD_Draw_Rectangle_Fill(0*15,19*15,15,15,COLOR_GREEN);
	LCD_Draw_Rectangle_Fill(1*15,19*15,15,15,COLOR_GREEN);
	LCD_Draw_Rectangle_Fill(1*15,18*15,15,15,COLOR_GREEN);
	LCD_Draw_Rectangle_Fill(2*15,18*15,15,15,COLOR_GREEN);
	// Z block
	LCD_Draw_Rectangle_Fill(4*15,9*15,15,15,COLOR_RED);
	LCD_Draw_Rectangle_Fill(4*15,10*15,15,15,COLOR_RED);
	LCD_Draw_Rectangle_Fill(5*15,10*15,15,15,COLOR_RED);
	LCD_Draw_Rectangle_Fill(5*15,11*15,15,15,COLOR_RED);
	// T block
	LCD_Draw_Rectangle_Fill(7*15,3*15,15,15,COLOR_PURPLE);
	LCD_Draw_Rectangle_Fill(8*15,4*15,15,15,COLOR_PURPLE);
	LCD_Draw_Rectangle_Fill(7*15,4*15,15,15,COLOR_PURPLE);
	LCD_Draw_Rectangle_Fill(6*15,4*15,15,15,COLOR_PURPLE);
	// Display back ground
	LCD_Draw_Tetris_Grid();
	// Display game title
	DisplayString(30, 20, "Tetris");

	// Draw button and label for START
	LCD_Draw_Rectangle_Fill(30, 200, 100, 70, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	DisplayString(40, 225, "START");


    while (1) {
        if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
            // Check touch coordinates for button presses
            if (StaticTouchData.x >= 100 && StaticTouchData.x <= 200) { // Horizontal bounds
                // START
                if (StaticTouchData.y >= 200 && StaticTouchData.y <= 270) {
                    LCD_Clear(0, LCD_COLOR_WHITE);
                    return true;  // Return true for START
                }
            }
        }
    }
}
bool Game_Select_2(int score, int playtime, int single, int doubles, int triple, int tetris, int PB){
	LCD_Clear(0,LCD_COLOR_WHITE);  // Clear the LCD display
	LCD_SetTextColor(LCD_COLOR_BLACK);  // Set text color to black
	LCD_SetFont(&Font16x24);  // Set font size

	// Print out all 7 blocks
	// I block
	LCD_Draw_Rectangle_Fill(1*15,1*15,15,15,COLOR_CYAN);
	LCD_Draw_Rectangle_Fill(1*15,2*15,15,15,COLOR_CYAN);
	LCD_Draw_Rectangle_Fill(1*15,3*15,15,15,COLOR_CYAN);
	LCD_Draw_Rectangle_Fill(1*15,4*15,15,15,COLOR_CYAN);
	// J block
	LCD_Draw_Rectangle_Fill(2*15,6*15,15,15,COLOR_BLUE);
	LCD_Draw_Rectangle_Fill(2*15,7*15,15,15,COLOR_BLUE);
	LCD_Draw_Rectangle_Fill(3*15,7*15,15,15,COLOR_BLUE);
	LCD_Draw_Rectangle_Fill(4*15,7*15,15,15,COLOR_BLUE);
	// L block
	LCD_Draw_Rectangle_Fill(7*15,10*15,15,15,COLOR_ORANGE);
	LCD_Draw_Rectangle_Fill(8*15,10*15,15,15,COLOR_ORANGE);
	LCD_Draw_Rectangle_Fill(9*15,10*15,15,15,COLOR_ORANGE);
	LCD_Draw_Rectangle_Fill(9*15,9*15,15,15,COLOR_ORANGE);
	// O block
	LCD_Draw_Rectangle_Fill(8*15,18*15,15,15,COLOR_YELLOW);
	LCD_Draw_Rectangle_Fill(8*15,19*15,15,15,COLOR_YELLOW);
	LCD_Draw_Rectangle_Fill(9*15,18*15,15,15,COLOR_YELLOW);
	LCD_Draw_Rectangle_Fill(9*15,19*15,15,15,COLOR_YELLOW);
	// S block
	LCD_Draw_Rectangle_Fill(0*15,19*15,15,15,COLOR_GREEN);
	LCD_Draw_Rectangle_Fill(1*15,19*15,15,15,COLOR_GREEN);
	LCD_Draw_Rectangle_Fill(1*15,18*15,15,15,COLOR_GREEN);
	LCD_Draw_Rectangle_Fill(2*15,18*15,15,15,COLOR_GREEN);
	// Z block
	LCD_Draw_Rectangle_Fill(4*15,9*15,15,15,COLOR_RED);
	LCD_Draw_Rectangle_Fill(4*15,10*15,15,15,COLOR_RED);
	LCD_Draw_Rectangle_Fill(5*15,10*15,15,15,COLOR_RED);
	LCD_Draw_Rectangle_Fill(5*15,11*15,15,15,COLOR_RED);
	// T block
	LCD_Draw_Rectangle_Fill(7*15,3*15,15,15,COLOR_PURPLE);
	LCD_Draw_Rectangle_Fill(8*15,4*15,15,15,COLOR_PURPLE);
	LCD_Draw_Rectangle_Fill(7*15,4*15,15,15,COLOR_PURPLE);
	LCD_Draw_Rectangle_Fill(6*15,4*15,15,15,COLOR_PURPLE);
	// Display back ground
	LCD_Draw_Tetris_Grid();
	// Display game title
	DisplayString(30, 20, "Tetris");

	// Draw button and label for START
	LCD_Draw_Rectangle_Fill(30, 200, 100, 70, LCD_COLOR_BLACK);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	DisplayString(40, 225, "START");


	LCD_SetTextColor(LCD_COLOR_BLACK);
	DisplayString(155, 10, "SCORE");
	char formatted[6];
	itoa(score, &formatted, 10);
	DisplayString(170, 50, formatted);
	DisplayString(180, 70, "PB");
	itoa(PB, &formatted, 10);
	DisplayString(170, 100, formatted);

	DisplayString(165, 150, "Time");
	itoa(playtime, &formatted, 10);
	DisplayString(170, 170, formatted);

	DisplayString(155, 230, "1X");
	DisplayString(155, 250, "2X");
	DisplayString(155, 270, "3X");
	DisplayString(155, 290, "4X");
	itoa(single, &formatted, 10);
	DisplayString(195, 230, formatted);
	itoa(doubles, &formatted, 10);
	DisplayString(195, 250, formatted);
	itoa(triple, &formatted, 10);
	DisplayString(195, 270, formatted);
	itoa(tetris, &formatted, 10);
	DisplayString(195, 290, formatted);
	while (1) {
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			// Check touch coordinates for button presses
			if (StaticTouchData.x >= 100 && StaticTouchData.x <= 200) { // Horizontal bounds
				// START
				if (StaticTouchData.y >= 200 && StaticTouchData.y <= 270) {
					LCD_Clear(0, LCD_COLOR_WHITE);
					return true;  // Return true for START
				}
			}
		}
	}
}



