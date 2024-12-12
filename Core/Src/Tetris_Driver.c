#include "Tetris_Driver.h"

// Grid array
uint16_t grid[GRID_HEIGHT][GRID_WIDTH];

// Tetrimino shapes
int Tetriminoes[7][4][4] = {
    // I-Tetrimino
    {{0,COLOR_CYAN,0,0},
     {0,COLOR_CYAN,0,0},
     {0,COLOR_CYAN,0,0},
     {0,COLOR_CYAN,0,0}},
    // O-Tetrimino
    {{0,0,0,0},
     {0,COLOR_YELLOW,COLOR_YELLOW,0},
     {0,COLOR_YELLOW,COLOR_YELLOW,0},
     {0,0,0,0}},
    // T-Tetrimino
    {{0,0,0,0},
     {0,COLOR_PURPLE,0,0},
     {COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,0},
     {0,0,0,0}},
    // S-Tetrimino
    {{0,0,0,0},
     {0,COLOR_GREEN,COLOR_GREEN,0},
     {COLOR_GREEN,COLOR_GREEN,0,0},
     {0,0,0,0}},
    // Z-Tetrimino
    {{0,0,0,0},
     {COLOR_RED,COLOR_RED,0,0},
     {0,COLOR_RED,COLOR_RED,0},
     {0,0,0,0}},
    // J-Tetrimino
    {{0,0,0,0},
     {COLOR_BLUE,0,0,0},
     {COLOR_BLUE,COLOR_BLUE,COLOR_BLUE,0},
     {0,0,0,0}},
    // L-Tetrimino
    {{0,0,0,0},
     {0,0,COLOR_ORANGE,0},
     {COLOR_ORANGE,COLOR_ORANGE,COLOR_ORANGE,0},
     {0,0,0,0}}
};

void InitializeGrid(void){
    for(int y = 0; y < GRID_HEIGHT; y++){
        for(int x = 0; x < GRID_WIDTH; x++){
            grid[y][x] = COLOR_NONE;
        }
    }
    //print score
        LCD_Draw_Rectangle_Fill(155,0,85,100,LCD_COLOR_BLACK);
        LCD_SetTextColor(LCD_COLOR_WHITE);
        DisplayString(160, 10, "SCORE");
		DisplayString(180, 50, "0");
}

void PrintGrid(void) {
    for(int y = 0; y < GRID_HEIGHT; y++){
        for(int x = 0; x < GRID_WIDTH; x++){
        	LCD_Draw_Rectangle_Fill(x*15,y*15,15,15,grid[y][x]);
        }
    }
    LCD_Draw_Tetris_Grid();
}

void removeTetrimino(int shape[4][4], int x, int y){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(shape[i][j] != COLOR_NONE){
				grid[y + i][x + j] = COLOR_NONE;
			}
		}
	}
}

bool PlaceTetrimino(int shape[4][4], int x, int y){
    if(CheckCollision(shape, x, y)){
        return false;
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(shape[i][j] != COLOR_NONE){
                grid[y + i][x + j] = shape[i][j];
            }
        }
    }
    return true;
}

// -1 for left, 1 for right, 0 for down
bool MoveTetrimino(int shape[4][4], int *x, int *y, int direction){
    int newX = *x;
    int newY = *y;

    if(direction == -1){
        newX -= 1;  // Move left
    }else if(direction == 1){
        newX += 1;  // Move right
    }else if(direction == 0){
        newY += 1;  // Move down
    }
    removeTetrimino(shape, *x, *y); // REMOVE old
    if(!CheckCollision(shape, newX, newY)){
        *x = newX;
        *y = newY;
        PlaceTetrimino(shape, *x, *y); // place new
        return true;
    }
    PlaceTetrimino(shape, *x, *y); // place back old
    return false;
}

void RotateTetrimino(int currentShape[4][4], int x, int y){
    int temp[4][4];

    // Copy the rotated shape into the temporary array
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            temp[i][j] = currentShape[3 - j][i];
        }
    }
    removeTetrimino(currentShape, x, y); // remove old
    // Check if the rotated shape can be placed in the current position
    if(!CheckCollision(temp, x, y)){
        // Copy the temporary array back to the original shape array
        for(int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
            	currentShape[i][j] = temp[i][j];
            }
        }
    }
    PlaceTetrimino(currentShape, x, y);// place back either new or old
}

bool CheckCollision(int shape[4][4], int x, int y){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(shape[i][j] != COLOR_NONE){
                int newX = x + j;
                int newY = y + i;
                if(newX < 0 || newX >= GRID_WIDTH || newY < 0 || newY >= GRID_HEIGHT || grid[newY][newX] != COLOR_NONE){
                    return true;
                }
            }
        }
    }
    return false;
}

void ClearLines(int *score, int *single, int *doubles, int *triple, int *tetris){
    int linesCleared = 0;

    for(int y = 0; y < GRID_HEIGHT; y++){//Check each level
        bool fullLine = true;
        for(int x = 0; x < GRID_WIDTH; x++){//Check full line
            if(grid[y][x] == COLOR_NONE){
                fullLine = false;
                break;
            }
        }
        if(fullLine){
            linesCleared++;
            for(int k = y; k > 0; k--){
                for(int x = 0; x < GRID_WIDTH; x++){
                    grid[k][x] = grid[k - 1][x];
                }
            }
            for(int x = 0; x < GRID_WIDTH; x++){
                grid[0][x] = COLOR_NONE;
            }
        }
    }

    // Add points to the score based on the number of lines cleared
    switch (linesCleared) {
        case 1:
            *score += 100; // 100 points for 1 line
            *single += 1;
            break;
        case 2:
            *score += 300; // 300 points for 2 lines
            *doubles += 1;
            break;
        case 3:
            *score += 500; // 500 points for 3 lines
            *triple += 1;
            break;
        case 4:
            *score += 800; // 800 points for 4 lines
            *tetris += 1;
            break;
        default:
            break;
    }
    if(linesCleared > 0){
    	LCD_Draw_Rectangle_Fill(155,0,85,100,LCD_COLOR_BLACK);
		LCD_SetTextColor(LCD_COLOR_WHITE);
		DisplayString(160, 10, "SCORE");
		char formatted[6];
		itoa(*score, &formatted, 10);
		DisplayString(180, 50, formatted);
    }
}


bool SpawnTetrimino(int currentShape[4][4], int *x, int *y){
	int num = RNG_Generate()%7;
	for(int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			currentShape[i][j] = Tetriminoes[num][i][j];
		}
	}
    *x = 3; 
    *y = 0;
    return PlaceTetrimino(currentShape, *x, *y);
}

