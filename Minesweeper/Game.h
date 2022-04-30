#pragma once

#include "Common.h"
#include <iostream>

const int CELL_HEIGHT = 3;
const int CELL_LENGTH = 3;

class Game {
private:
	int _size = 0;
	int _numOfMines = 0;
	int _numOfFlags = 0;
	int _flagsPlaced = 0;
	int _cellsDigged = 0;
	bool** _minesMap = nullptr;

public:
	Game();
	~Game();

	void setUpGame(int);
	void generateGameData(int);
	void renderGameData(int);
	void drawGame(int);
};