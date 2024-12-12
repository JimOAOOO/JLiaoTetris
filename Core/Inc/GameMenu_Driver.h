#ifndef INC_GAMEMENU_DRIVER_H_
#define INC_GAMEMENU_DRIVER_H_

#include <stdbool.h>
#include <stdio.h>
#include "RNG_Driver.h"

// Function declaration for selecting the game mode.
// This function  allows the user to choose between different modes of play
bool Game_Select(void);

bool Game_Select_2(int score, int playtime, int single, int doubles, int triple, int tetris, int PB);

// Function to display a string on the LCD at a specific location.
void DisplayString(uint16_t x, uint16_t y, char *str);

#endif /* INC_GAMEMENU_DRIVER_H_ */
