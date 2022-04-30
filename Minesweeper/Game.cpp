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

	//Initializing _minesMap
	_minesMap = new bool*[size];
	for (int i = 0; i < size; i++) _minesMap[i] = new bool[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			_minesMap[i][j] = 0;

	bool* checkDuplicate = new bool[size * size];
	for (int i = 0; i < size * size; i++) checkDuplicate[i] = 0;

	srand(time(0));
	int n = _numOfMines;
	while (n) {
		int i = rand() % (size * size);
		if (!checkDuplicate[i]) {
			checkDuplicate[i] = 1;
			_minesMap[i % size][i / size] = 1;
			n--;
		}
	}
}

void Game::renderGameData(int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << _minesMap[i][j] << " ";
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