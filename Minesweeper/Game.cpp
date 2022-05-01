﻿#include "Game.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {
	delete[]_cellsMap;
}

//////////////////////////////////////////////////////

void Game::playGame(int size)
{
	_size = size;
	setupGame();

	std::pair<int, int> currCell = { 0, 0 };		//Initialize selected cell 
	selectCell(currCell);

	int c = 1;
	while (c) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:				//Up
			if (currCell.second == 0) break;
			unselectCell(currCell);
			currCell.second--;
			selectCell(currCell);
			break;
		case 3:				//Left
			if (currCell.first == 0) break;
			unselectCell(currCell);
			currCell.first--;
			selectCell(currCell);
			break;
		case 4:				//Right
			if (currCell.first == _size - 1) break;
			unselectCell(currCell);
			currCell.first++;
			selectCell(currCell);
			break;
		case 5:				//Down
			if (currCell.second == _size - 1) break;
			unselectCell(currCell);
			currCell.second++;
			selectCell(currCell);
			break;
		case 6:				//Enter
			break;
		case 7:				//J, j(dig)
			if (_cellsMap[currCell.second][currCell.first].getMine()) exit(1);
			countNumOfMines(currCell);
			_cellsMap[currCell.first][currCell.second].setStatus(0);
			selectCell(currCell);
			break;
		case 8:				//K, k(flag)
			break;
		default:break;
		}
	}
}

void Game::setupGame() {
	Common::clearConsole();
	drawGame();
	generateGameData();
	renderGameData(); 
}

void Game::generateGameData()
{
	switch (_size)
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

	_cellsMap = new Cells * [_size];
	for (int i = 0; i < _size; i++)
		_cellsMap[i] = new Cells[_size];

	int n = _numOfMines;
	srand(time(0));
	while (n) {
		int i = rand() % (_size * _size);
		if (!_cellsMap[i % _size][i / _size].getMine()) {
			_cellsMap[i % _size][i / _size].setMine(1);
			n--;
		}
	}
}

void Game::renderGameData()
{
	int left = _left + 2, top = _top + 1;
	for (int i = 0; i < _size * CELL_HEIGHT; i += CELL_HEIGHT) {
		for (int j = 0; j < _size * CELL_LENGTH; j += CELL_LENGTH) {
			Common::gotoXY(left + j, top + i);
			std::cout << _cellsMap[i / CELL_HEIGHT][j / CELL_LENGTH].getMine();
		}
	}
}

void Game::drawGame() {//vẽ ra bảng game
	if (_size == 10) {
		_left = 45;
		_top = 6;
	}
	else if (_size == 15) {
		_left = 35;
		_top = 1;
	}
	drawHorizontalLine();
	drawVerticalLine();
	drawCorner();
	drawLinkLine();
}

//////////////////////////////////////////////////////

void Game::drawHorizontalLine() {
	for (int i = 0; i <= CELL_HEIGHT * _size; i += CELL_HEIGHT) {
		Common().gotoXY(_left, _top + i);
		for (int j = 0; j <= CELL_LENGTH * _size; j++) {
			putchar(205);
		}
	}
}

void Game::drawVerticalLine() {
	for (int i = 0; i <= CELL_LENGTH * _size; i+=CELL_LENGTH) {
		for (int j = 0; j <= CELL_HEIGHT * _size; j++) {
			Common::gotoXY(_left + i, _top + j);
			putchar(186);
		}
	}
}

void Game::drawCorner() {
	Common().gotoXY(_left, _top); //  tren ben trai
	putchar(201);

	Common().gotoXY(_left + CELL_LENGTH * _size, _top); // tren ben phai
	putchar(187);

	Common().gotoXY(_left, _top + CELL_HEIGHT * _size); // duoi ben trai
	putchar(200);

	Common().gotoXY(_left + CELL_LENGTH * _size, _top + CELL_HEIGHT * _size); // duoi ben phai
	putchar(188);
}

void Game::drawLinkLine()
{
	for (int i = CELL_LENGTH; i < CELL_LENGTH * _size; i += CELL_LENGTH) {
		Common().gotoXY(_left + i, _top);
		putchar(203);
		Common().gotoXY(_left + i, _top + CELL_HEIGHT * _size);
		putchar(202);
	}

	for (int i = CELL_HEIGHT; i < CELL_HEIGHT * _size; i += CELL_HEIGHT) {
		Common().gotoXY(_left, _top + i);
		putchar(204);
		Common().gotoXY(_left + CELL_LENGTH * _size, _top + i);
		putchar(185);
	}

	for (int i = CELL_LENGTH; i < CELL_LENGTH * _size; i += CELL_LENGTH) {
		for (int j = CELL_HEIGHT; j < CELL_HEIGHT * _size; j += CELL_HEIGHT) {
			Common().gotoXY(_left + i, _top + j);
			putchar(206);
		}
	}
}

//////////////////////////////////////////////////////

std::pair<int, int> Game::convertCoord(int left, int top)//currently useless
{
	return std::pair<int, int>((left - _left) / CELL_LENGTH, (top - _top) / CELL_HEIGHT);//?
}

void Game::selectCell(std::pair<int, int> currCell)
{
	Common::setConsoleColor(RED, BRIGHT_WHITE);
	for (int i = 1; i <= 3; i++) {
		Common::gotoXY(_left + currCell.first*CELL_LENGTH + i, _top + currCell.second*CELL_HEIGHT + 1);
		putchar(' ');
	}

	if (!_cellsMap[currCell.first][currCell.second].getStatus()) {
		Common::gotoXY(_left + currCell.first * CELL_LENGTH + 2, _top + currCell.second * CELL_HEIGHT + 1);
		std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
		return;
	}
}

void Game::unselectCell(std::pair<int, int> currCell)
{
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);

	for (int i = 1; i <= 3; i++) {
		Common::gotoXY(_left + currCell.first * CELL_LENGTH + i, _top + currCell.second * CELL_HEIGHT + 1);
		putchar(' ');
	}

	if (!_cellsMap[currCell.first][currCell.second].getStatus()) {
		Common::gotoXY(_left + currCell.first * CELL_LENGTH + 2, _top + currCell.second * CELL_HEIGHT + 1);
		int num = _cellsMap[currCell.first][currCell.second].getNumOfMines();
		switch (num) {
		case 1:
			Common::setConsoleColor(BLACK, BLUE);
			std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
			break;
		case 2:
			Common::setConsoleColor(BLACK, GREEN);
			std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
			break;
		case 3:
			Common::setConsoleColor(BLACK, RED);
			std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
			break;
		case 4:
			Common::setConsoleColor(BLACK, PURPLE);
			std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			Common::setConsoleColor(BLACK, LIGHT_AQUA);
			std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
			break;
		}
		return;
	}
}

void Game::countNumOfMines(std::pair<int, int> currCell)//count number of mines around a cell
{
	//currCell chỉ là tọa độ của cell đang chọn
	//phải chuyển vào tọa độ của _cellsMap
	int count = 0;
	int i = currCell.second - 1;
	int j = currCell.first - 1;

	

	for (int k = i; k <= currCell.second + 1; k++)
	{
		for (int l = j; l <= currCell.first + 1; l++)
		{
			if (_cellsMap[k][l].getMine()) count++;
		}
	}

	_cellsMap[currCell.first][currCell.second].setNumOfMines(count);
}
