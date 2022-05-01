#pragma once

#include "Common.h"
#include "Cell.h"
#include <iostream>

const int CELL_HEIGHT = 2;
const int CELL_LENGTH = 4;

class Game {
private:
	int _numOfMines = 0;
	int _numOfFlags = 0;
	int _flagsPlaced = 0;
	int _cellsDigged = 0;
	bool** _minesMap = nullptr;
	Cells** _cellsMap;

public:
	int _left = 0, _top = 0, _size = 0;//Position of board game and board size
	Game();
	~Game();

	///////////////////////////////////////

	void setupGame();
	void playGame(int);
	void generateGameData();
	void renderGameData();
	void drawGame();

	///////////////////////////////////////

	void drawHorizontalLine();
	void drawVerticalLine();
	void drawCorner();
	void drawLinkLine();

	///////////////////////////////////////

	std::pair<int, int> convertCoord(int, int);
	void selectCell(std::pair<int, int>);
	void unselectCell(std::pair<int, int>);
};