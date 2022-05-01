#include "Game.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::setUpGame(int size) {
	Common::clearConsole();
	drawGame(size);
	generateGameData(size);
	renderGameData(size); 
}

void Game::generateGameData(int size)
{
	switch (size)
	{
	case 10:
		_numOfMines = 20;
		break;
	case 15:
		_numOfMines = 40;
		break;
	case 25:
		_numOfMines = 100;
	default:
		break;
	}

	_cellsMap = new Cells * [size];
	for (int i = 0; i < size; i++)
		_cellsMap[i] = new Cells[size];

	int n = _numOfMines;
	srand(time(0));
	while (n) {
		int i = rand() % (size * size);
		if (!_cellsMap[i % size][i / size].getMine()) {
			_cellsMap[i % size][i / size].setMine(1);
			n--;
		}
	}
}

void Game::renderGameData(int size)
{
	int left = 2, top = 1;
	for (int i = 0; i < size * CELL_HEIGHT; i += CELL_HEIGHT) {
		for (int j = 0; j < size * CELL_LENGTH; j += CELL_LENGTH) {
			Common::gotoXY(left + j, top + i);
			std::cout << _cellsMap[i / CELL_HEIGHT][j / CELL_LENGTH].getMine();
		}
	}
	Sleep(20000);
}

void Game::drawGame(int size) {//vẽ ra bảng game
	int left = 0, top = 0;
	drawHorizontalLine(size,left, top);
	drawVerticalLine(size, left, top);
	drawCorner(size, left, top);
	drawLinkLine(size, left, top);
}

void Game::drawHorizontalLine(int size, int left, int top) {
	for (int i = 0; i <= CELL_HEIGHT * size; i += CELL_HEIGHT) {
		Common().gotoXY(left, top + i);
		for (int j = 0; j <= CELL_LENGTH * size; j++) {
			putchar(205);
		}
	}
}

void Game::drawVerticalLine(int size, int left, int top) {
	for (int i = 0; i <= CELL_LENGTH * size; i+=CELL_LENGTH) {
		for (int j = 0; j <= CELL_HEIGHT * size; j++) {
			Common::gotoXY(left + i, top + j);
			putchar(186);
		}
	}
}

void Game::drawCorner(int size, int left, int top) {
	Common().gotoXY(left, top); //  tren ben trai
	putchar(201);

	Common().gotoXY(left + CELL_LENGTH * size, top); // tren ben phai
	putchar(187);

	Common().gotoXY(left, top + CELL_HEIGHT * size); // duoi ben trai
	putchar(200);

	Common().gotoXY(left + CELL_LENGTH * size, top + CELL_HEIGHT * size); // duoi ben phai
	putchar(188);
}

void Game::drawLinkLine(int size, int left, int top)
{
	for (int i = CELL_LENGTH; i < CELL_LENGTH * size; i += CELL_LENGTH) {
		Common().gotoXY(left + i, top);
		putchar(203);
		Common().gotoXY(left + i, top + CELL_HEIGHT * size);
		putchar(202);
	}

	for (int i = CELL_HEIGHT; i < CELL_HEIGHT * size; i += CELL_HEIGHT) {
		Common().gotoXY(left, top + i);
		putchar(204);
		Common().gotoXY(left + CELL_LENGTH * size, top + i);
		putchar(185);
	}

	for (int i = CELL_LENGTH; i < CELL_LENGTH * size; i += CELL_LENGTH) {
		for (int j = CELL_HEIGHT; j < CELL_HEIGHT * size; j += CELL_HEIGHT) {
			Common().gotoXY(left+i, top + j);
			putchar(206);
		}
	}
}
