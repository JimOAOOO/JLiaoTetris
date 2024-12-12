#ifndef INC_TETRIS_DRIVER_H_
#define INC_TETRIS_DRIVER_H_

#include "GameMenu_Driver.h"

#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define CELL_SIZE 15
#define FALL_TIME 300 //in ms
enum {
    COLOR_NONE = 0x0000,    // Black
    COLOR_CYAN = 0x07FF,    // I-Tetrimino
    COLOR_YELLOW = 0xFFE0,  // O-Tetrimino
    COLOR_PURPLE = 0xF81F,  // T-Tetrimino
    COLOR_GREEN = 0x07E0,   // S-Tetrimino
    COLOR_RED = 0xF800,     // Z-Tetrimino
    COLOR_BLUE = 0x001F,    // J-Tetrimino
    COLOR_ORANGE = 0xFD20   // L-Tetrimino
};

// Function prototypes
void InitializeGrid(void);
void PrintGrid(void);
void removeTetrimino(int shape[4][4], int x, int y);
bool PlaceTetrimino(int shape[4][4], int x, int y);
bool MoveTetrimino(int shape[4][4], int *x, int *y, int direction);
void RotateTetrimino(int currentShape[4][4], int x, int y);
bool CheckCollision(int shape[4][4], int x, int y);
void ClearLines(int *score, int *single, int *doubles, int *triple, int *tetris);
bool SpawnTetrimino(int currentShape[4][4], int *x, int *y);

#endif /* INC_TETRIS_DRIVER_H_ */
