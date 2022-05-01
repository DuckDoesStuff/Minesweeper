#pragma once

#include "Common.h"
#include "Cell.h"
#include <iostream>

const int CELL_HEIGHT = 2;
const int CELL_LENGTH = 4;

class Game {
private:
	int _size = 0;
	int _numOfMines = 0;
	int _numOfFlags = 0;
	int _flagsPlaced = 0;
	int _cellsDigged = 0;
	bool** _minesMap = nullptr;
	Cells** _cellsMap;

public:
	Game();
	~Game();

	void setUpGame(int);
	void generateGameData(int);
	void renderGameData(int);
	void drawGame(int);
	void drawHorizontalLine(int, int, int);
	void drawVerticalLine(int, int, int);
	void drawCorner(int size, int left, int top);
};