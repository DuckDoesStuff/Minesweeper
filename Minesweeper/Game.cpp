#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::setUpGame(int size) {
	Common::clearConsole();
	//drawGame(size);
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
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << _cellsMap[i][j].getMine() << " ";
		}
		std::cout << '\n';
	}
	Sleep(20000);
}

void Game::drawGame(int size) {//vẽ ra bảng game
	int left = 0, top = 0;

	Common::gotoXY(left, top);
	for (int i = 0; i < CELL_LENGTH * size; i++) {
		putchar(205);
	}
}