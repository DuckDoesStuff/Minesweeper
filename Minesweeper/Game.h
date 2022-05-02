#pragma once

#include "Common.h"
#include "Cell.h"
#include <iostream>

const int CELL_HEIGHT = 2;
const int CELL_LENGTH = 4;
const int LDBOARD_MX = 5;
const int LDBOARD_MY = 0;
const int LDBOARD_LENGTH = 26;
const int LDBOARD_HEIGHT = 16;

class Game {
private:

	int _numOfMines = 0;
	int _flagsPlaced = 0;			//Moi lan flag ++
	int _cellsDigged = 0;			//Moi lan dig ++
	Cells** _cellsMap;

public:

	int _left = 0, _top = 0, _size = 0;			//Position of board game and board size
	Game();
	~Game();

	//////////////////////////////////////////////////////

	void setupGame();
	void playGame(int);
	void generateGameData();
	void generateNumOfMines();
	void generateMines();
	void placeFlag(std::pair<int, int> currCell);
	void renderGameData();
	void drawGame();

	//////////////////////////////////////////////////////

	void drawHorizontalLine();
	void drawVerticalLine();
	void drawCorner(int, int,int , int);
	void drawLinkLine();
	void drawUnDugCells();
	void drawSideLineY(int x, int y, int length,int type);
	void outputText(int x, int y, std::string, int margin);
	void outputIcon(int x, int y, int id, int margin);
	void drawLeaderBoard();

	//////////////////////////////////////////////////////

	std::pair<int, int> convertCoord(int, int);
	void selectCell(std::pair<int, int>);
	void colorCell(std::pair <int, int>);
	void unselectCell(std::pair<int, int>);
	void countNumOfMines(std::pair<int, int>);
	void digNeighbor(std::pair<int, int>);
};