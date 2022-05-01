#pragma once

#include "Common.h"

const int CELL_HEIGHT = 3;
const int CELL_LENGTH = 5;

class Game {
private:
	int size;
	int mumOfMines;
	int numOfFlags;
	int flagsPlaced = 0;
	int cellsDigged = 0;

public:
	Game();
	~Game();

	void setUpGame(int);
	void drawGame(int);
	void drawHorizontalLine(int, int, int);
	void drawVerticalLine(int, int, int);
	void drawCorner(int, int, int);
};