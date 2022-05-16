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
	//_player->askPlayerName();
	Common::clearConsole();
	setupGame();
	//danh dau moc thoi gian bat dau

	selectCell(_currCell);
	countNumOfMinesAll();

	firstHit();

	std::pair<int, int> currCell = _currCell;	//Initialize selecting cell
	selectCell(currCell);

	int c = 0, count = 0;

	while (_finish == 0) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:							//Up
			moveUp(currCell);
			break;
		case 3:							//Left
			moveLeft(currCell);
			break;
		case 4:							//Right
			moveRight(currCell);
			break;
		case 5:							//Down
			moveDown(currCell);
			break;
		case 6:							//Enter
			break;
		case 7:							//J, j(dig)
			digCell(currCell);
			break;
		case 8:							//K, k(flag)
			placeFlag(currCell);
			break;
		case 9:							//L, l(auto flag or dig
			autoFlagAndDig(currCell);
			break;
		default:break;
		}
		Common::setConsoleColor(BLACK, BRIGHT_WHITE);
		Common::gotoXY(0, 0);
		std::cout << "                                                                                  ";
		Common::gotoXY(0, 0);
		std::cout << _flagsPlaced << "   " << _cellsDigged << "   " << _numOfMines << "   " << _finish;
	}
	//Sleep(1000);
	_currCell = currCell;

	//xu ly sau khi ket thuc 1 van game
	 
	endGame();
}

void Game::firstHit()
{
	int c;
	bool dug = false;
	while (!dug) {
		c = Common::getConsoleInput();
		switch (c) {
		case 2:							//Up
			moveUp(_currCell);
			break;
		case 3:							//Left
			moveLeft(_currCell);
			break;
		case 4:							//Right
			moveRight(_currCell);
			break;
		case 5:							//Down
			moveDown(_currCell);
			break;
		case 6:							//Enter
			break;
		case 7:							//J, j(dig)
			dug = true;
			break;
		case 8:							//K, k(flag)
			placeFlag(_currCell);
			break;
		case 9:							//L, l(auto flag and dig)
		default:break;
		}
	}

	std::pair<short, short> start, end;

	start.first = _currCell.first - 1;
	start.second = _currCell.second - 1;
	end.first = _currCell.first + 1;
	end.second = _currCell.second + 1;

	if (_currCell.first == 0) start.first++;
	else if (_currCell.first == _size - 1) end.first--;

	if (_currCell.second == 0) start.second++;
	else if (_currCell.second == _size - 1) end.second--;

	short count = 0;
	for (short i = start.second; i <= end.second; i++) {
		for (short j = start.first; j <= end.first; j++) {
			if (_cellsMap[j][i].getMine() == 1) {
				count++;
				_cellsMap[j][i].setMine(0);
			}
		}
	}
	if (count == 0) {
		digCell(_currCell);
		return;
	}
	srand(time(0));
	while (count) {
		int i = rand() % (_size * _size);
		if (!(i % _size >= start.first && 
			i % _size <= end.first && 
			i / _size >= start.second && 
			i / _size <= end.second) &&
			!_cellsMap[i % _size][i / _size].getMine()) {
			_cellsMap[i % _size][i / _size].setMine(1);
			count--;
		}
	}
	countNumOfMinesAll();
	digCell(_currCell);
}

void Game::setupGame() {
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
	drawGame();
	generateGameData();
	_flagsPlaced = 0;
	_cellsDigged = 0;
	_currCell = { 0, 0 };
	_finish = 0;
}

void Game::generateGameData()
{
	switch (_size)
	{
	case 10:
		_numOfMines = 10;
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
	for (int i = 0; i < _size; i++) {
		_cellsMap[i] = new Cells[_size];
	}

	int n = _numOfMines;
	//srand(time(0));
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
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
	int left = 2, top = 1;
	for (int i = 0; i < _size * CELL_HEIGHT; i += CELL_HEIGHT) {
		for (int j = 0; j < _size * CELL_LENGTH; j += CELL_LENGTH) {
			Common::gotoXY(left + j, top + i);
			std::cout << _cellsMap[j / CELL_LENGTH][i / CELL_HEIGHT].getNumOfMines();
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
	drawCorner(_left, _top, CELL_LENGTH * _size, CELL_HEIGHT * _size);
	drawLinkLine();
	drawUnDugCells();
	drawLeaderBoard();
}

void Game::revealMines()
{
	//reveal _currCell
	//reveal other cells around _currCell in random color
}

void Game::winScreen()
{
	int left = 0, top = 0;
	Common::setConsoleColor(BLACK, BLUE);
	Common::clearConsole();
	std::ifstream in("Titles\\WinScreen.txt");

	std::string s;
	int i = 0;
	while (!in.eof()) {
		getline(in, s);
		Common::gotoXY(left, top + i);
		std::cout << s;
		i++;
	}

	in.close();
	Sleep(2000);
}

void Game::tryAgain()
{
	int left = 0, top = 0;
	Common::setConsoleColor(BLACK, BLUE);
	Common::clearConsole();
	std::ifstream in("Titles\\TryAgain.txt");

	std::string s;
	int i = 0;
	while (!in.eof()) {
		getline(in, s);
		Common::gotoXY(left, top + i);
		std::cout << s;
		i++;
	}

	in.close();
}

void Game::endGame()
{
	//danh dau moc thoi gian ket thuc
	//hien diem va thoi gian cua nguoi choi
	// _player->_time, _score
	//hien leaderboard
	//showLeaderboard()
	if (_finish == 1) winScreen();
	else if(_finish == 2) {
		tryAgain();
		if (Common::getConsoleInput() == 6) playGame(_size);
	}
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

void Game::drawCorner(int left, int top , int length, int height) {
	Common().gotoXY(left, top); //  tren ben trai
	putchar(201);

	Common().gotoXY(left + length, top); // tren ben phai
	putchar(187);

	Common().gotoXY(left, top + height); // duoi ben trai
	putchar(200);

	Common().gotoXY(left + length, top + height); // duoi ben phai
	putchar(188);
}

void Game::drawLinkLine()
{
	int length = CELL_LENGTH * _size;
	int height = CELL_HEIGHT * _size;
	for (int i = CELL_LENGTH; i < length; i += CELL_LENGTH) {
		Common().gotoXY(_left + i, _top);
		putchar(203);
		Common().gotoXY(_left + i, _top + height);
		putchar(202);
	}

	for (int i = CELL_HEIGHT; i < height; i += CELL_HEIGHT) {
		Common().gotoXY(_left, _top + i);
		putchar(204);
		Common().gotoXY(_left + length, _top + i);
		putchar(185);
	}

	for (int i = CELL_LENGTH; i < length; i += CELL_LENGTH) {
		for (int j = CELL_HEIGHT; j < height; j += CELL_HEIGHT) {
			Common().gotoXY(_left + i, _top + j);
			putchar(206);
		}
	}
}

void Game::drawUnDugCells()
{
	int left = _left + 2, top = _top + 1;
	Common::setConsoleColor(BLACK, GRAY);

	for (int i = 0; i < _size * CELL_HEIGHT; i += CELL_HEIGHT) {
		for (int j = 0; j < _size * CELL_LENGTH; j += CELL_LENGTH) {
			Common::gotoXY(left + j, top + i);
			putchar('0');
		}
	}

	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
}

void Game::drawSideLineY(int x, int y, int length, int type)
{
	Common::gotoXY(x, y);
	putchar(204);
	for (int i = 0; i < length - 1; i++) {
		putchar(type);
	}
	putchar(185);
}

void Game::outputText(int x, int y, std::string text, int margin)
{
	Common::gotoXY(x, y);
	for (int i = 0; i < margin; i++) {
		putchar(' ');
	}
	std::cout << text;
	for (int i = 0; i < margin; i++) {
		putchar(' ');
	}
}

void Game::outputIcon(int x, int y, int id, int margin)
{
	Common::gotoXY(x, y);
	for (int i = 0; i < margin; i++) {
		putchar(' ');
	}
	putchar(id);
	for (int i = 0; i < margin; i++) {
		putchar(' ');
	}
}

void Game::drawLeaderBoard()
{
	//name , time , flag , mode 
	int x = _left + CELL_LENGTH * _size + LDBOARD_MX;
	int y = _top + LDBOARD_MY;
	Common::setConsoleColor(BLACK, WHITE);
	for (int i = 0; i <= LDBOARD_LENGTH; i++) {
		Common::gotoXY(x + i, y);
		putchar(205);
		Common::gotoXY(x + i, y + LDBOARD_HEIGHT);
		putchar(205);
	}
	
	for (int i = 1; i <= LDBOARD_HEIGHT; i++) {
		Common::gotoXY(x, y + i);
		putchar(186);
		Common::gotoXY(x + LDBOARD_LENGTH, y + i);
		putchar(186);
	}
	//HEADER 
	int marginTop = 4;
	int marginX = 3;
	int padding = 2;
	drawCorner(x, y, LDBOARD_LENGTH, LDBOARD_HEIGHT);
	drawSideLineY(x, y + marginTop, LDBOARD_LENGTH,205);
	drawSideLineY(x, y + padding + 8, LDBOARD_LENGTH, 250);
	Common::setConsoleColor(BLACK, PURPLE);
	outputText(x + 2, y + padding, "SCORE BOARD", 6);
	Common::setConsoleColor(BLACK, RED);
	outputIcon(x + marginX, y + padding, 3, 0);
	outputIcon(x + LDBOARD_LENGTH - marginX, y + padding, 3, 0);
	Common::setConsoleColor(BLACK, LIGHT_PURPLE);
	outputText(x + marginX, y + padding + 4, "Name: ", 2);
	outputIcon(x + marginX - 1, y + padding + 4, 16, 1);
	outputText(x + marginX, y + padding + 6, "Mode: ", 2);
	outputIcon(x + marginX - 1, y + padding + 6, 16, 1);
	Common::setConsoleColor(BLACK, RED);
	outputText(x + marginX, y + padding + 10, "Flag: ", 2);
	outputIcon(x + marginX - 1, y + padding + 10, 35, 1);
	outputText(x + marginX, y + padding + 12, "Time: ", 2);
	outputIcon(x + marginX - 1, y + padding + 12, 232, 1);
}

//////////////////////////////////////////////////////

void Game::moveUp(std::pair<int, int> &currCell)
{
	if (currCell.second == 0) return;
	unselectCell(currCell);
	currCell.second--;
	selectCell(currCell);
}

void Game::moveLeft(std::pair<int, int> &currCell)
{
	if (currCell.first == 0) return;
	unselectCell(currCell);
	currCell.first--;
	selectCell(currCell);
}

void Game::moveRight(std::pair<int, int> &currCell)
{
	if (currCell.first == _size - 1) return;
	unselectCell(currCell);
	currCell.first++;
	selectCell(currCell);
}

void Game::moveDown(std::pair<int, int> &currCell)
{
	if (currCell.second == _size - 1) return;
	unselectCell(currCell);
	currCell.second++;
	selectCell(currCell);
}

//////////////////////////////////////////////////////

std::pair<int, int> Game::convertCoord(int left, int top)//currently useless
{
	return std::pair<int, int>((left - _left) / CELL_LENGTH, (top - _top) / CELL_HEIGHT);//?
}

void Game::selectCell(std::pair<int, int> &currCell)
{
	int x = _left + currCell.first * CELL_LENGTH;
	int y = _top + currCell.second * CELL_HEIGHT + 1;
	Common::setConsoleColor(RED, BRIGHT_WHITE);
	Common::gotoXY(x + 1, y);
	std::cout << "   ";
	if (cell.getFlag()) {		//show flag
		Common::gotoXY(x + 2, y);
		putchar(35);
		return;
	}
	if (cell.getStatus()) {	//show undug cell
		Common::setConsoleColor(RED, GRAY);	
		Common::gotoXY(x + 2, y);
		putchar('0');
		return;
	}
	Common::gotoXY(x + 2, y);
	if (cell.getNumOfMines() > 0) std::cout << cell.getNumOfMines();

}

void Game::colorCell(std::pair<int, int> &currCell)
{
	int x = _left + currCell.first * CELL_LENGTH + 2;
	int y = _top + currCell.second * CELL_HEIGHT + 1;
	Common::gotoXY(x, y);

	if (cell.getFlag()) {
		Common::setConsoleColor(BLACK, LIGHT_YELLOW);
		putchar(35);
		return;
	}

	if (cell.getStatus()) {
		Common::setConsoleColor(BLACK, GRAY);
		putchar('0');
		return;
	}
	else {
		Common::setConsoleColor(BLACK, BLACK);
		putchar(' ');
	}

	Common::gotoXY(x, y);

	int num = cell.getNumOfMines();
	if (num <= 0) return;

	switch (num) {
	case 1:
		Common::setConsoleColor(BLACK, LIGHT_BLUE);
		std::cout << cell.getNumOfMines();
		break;
	case 2:
		Common::setConsoleColor(BLACK, LIGHT_GREEN);
		std::cout << cell.getNumOfMines();
		break;
	case 3:
		Common::setConsoleColor(BLACK, LIGHT_RED);
		std::cout << cell.getNumOfMines();
		break;
	case 4:
		Common::setConsoleColor(BLACK, PURPLE);
		std::cout << cell.getNumOfMines();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		Common::setConsoleColor(BLACK, LIGHT_AQUA);
		std::cout << cell.getNumOfMines();
		break;
	}
	return;
}

void Game::unselectCell(std::pair<int, int> &currCell)
{
	int x = _left + currCell.first * CELL_LENGTH;
	int y = _top + currCell.second * CELL_HEIGHT + 1;
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
	for (int i = 1; i <= 3; i++) {
		Common::gotoXY(x + i, y);
		putchar(' ');
	}
	colorCell(currCell);
}

void Game::deleteMidLines(std::pair<int, int> &currCell)
{
	std::pair<short, short> tmp;
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
	int x,y;

	//Left cell
	if (currCell.first != 0) {
		tmp = { currCell.first - 1, currCell.second };
		x = _left + tmp.first * CELL_LENGTH + 4;
		y = _top + tmp.second * CELL_HEIGHT;
		if (_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0 &&
			_cellsMap[tmp.first][tmp.second].getFlag() == NOT_FLAGGED) {
			Common::gotoXY(x, y + 1);
			putchar(' ');
			Common::gotoXY(x, y);
			if (tmp.second == 0)
				putchar(205);
		}
	}

	//Right cell
	if (currCell.first != _size - 1) {
		tmp = { currCell.first + 1, currCell.second };
		x = _left + tmp.first * CELL_LENGTH;
		y = _top + tmp.second * CELL_HEIGHT;
		if (_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0 &&
			_cellsMap[tmp.first][tmp.second].getFlag() == NOT_FLAGGED) {
			Common::gotoXY(x, y + 1);
			putchar(' ');
			Common::gotoXY(x, y + 2);
			if (tmp.second == _size - 1)
				putchar(205);
		}
	}

	//Top cell
	if (currCell.second != 0) {
		tmp = { currCell.first, currCell.second - 1 };
		x = _left + tmp.first * CELL_LENGTH;
		y = _top + tmp.second * CELL_HEIGHT + 2;
		if (_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0 &&
			_cellsMap[tmp.first][tmp.second].getFlag() == NOT_FLAGGED) {
			Common::gotoXY(x + 1,y);
			std::cout << "   ";
			Common::gotoXY(x ,y);
			if (tmp.first == 0)
				putchar(186);
		}
	}

	//Bottom cell
	if (currCell.second != _size - 1) {
		tmp = { currCell.first, currCell.second + 1 };
		x = _left + tmp.first * CELL_LENGTH;
		y = _top + tmp.second * CELL_HEIGHT;
		if (_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0 &&
			_cellsMap[tmp.first][tmp.second].getFlag() == NOT_FLAGGED) {
			Common::gotoXY(x + 1, y);
			std::cout << "   ";
			Common::gotoXY(x + 4, y);
			if (tmp.first == _size - 1)
				putchar(186);
		}
	}
}

void Game::rotateJunctions(std::pair<int, int> &currCell)
{
	if (cell.getNumOfMines() > 0) return;
				//0 1 2
				//3 X 4
				//5 6 7
	bool checkBorder[4] = { false };
	short checkDigged[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	std::pair<short, short> start, end;

	start.first = currCell.first - 1;
	start.second = currCell.second - 1;
	end.first = currCell.first + 1;
	end.second = currCell.second + 1;

	if (currCell.first == 0) {
		checkBorder[1] = true;
		checkDigged[0] = 0;
		checkDigged[3] = 0;
		checkDigged[5] = 0;
		start.first++;
	}
	else if (currCell.first == _size - 1) {
		checkBorder[2] = true;
		checkDigged[2] = 0;
		checkDigged[4] = 0;
		checkDigged[7] = 0;
		end.first--;
	}

	if (currCell.second == 0) {
		checkBorder[0] = true;
		checkDigged[0] = 0;
		checkDigged[1] = 0;
		checkDigged[2] = 0;
		start.second++;
	}
	else if (currCell.second == _size - 1) {
		checkBorder[3] = true;
		checkDigged[5] = 0;
		checkDigged[6] = 0;
		checkDigged[7] = 0;
		end.second--;
	}

	int index = 0;
	for (short i = start.second; i <= end.second; i++) {
		for (short j = start.first; j <= end.first; j++) {
			if (currCell.first == j && currCell.second == i) continue;
			if (_cellsMap[j][i].getNumOfMines() == 0 &&
				_cellsMap[j][i].getFlag() == NOT_FLAGGED) {
				while (checkDigged[index] == 0) index++;
				checkDigged[index] = 1;
			}
			else {
				while (checkDigged[index] == 0) index++;
				checkDigged[index] = 0;
			}
			index++;
		}
	}
				//0 1 2
				//3 X 4
				//5 6 7
	for (int i = 0; i < 4; i++) {
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
		if (checkBorder[i / 2 + i / 3] || checkBorder[1 + i - i / 3]) continue;//might need to work on this later
		Common::gotoXY(_left + currCell.first * CELL_LENGTH + (i%2)*4, _top + currCell.second * CELL_HEIGHT + (i/2)*2);
		if (checkDigged[i + (i % 2) + (i / 2) * 3] &&	//corner
			checkDigged[1 + (i / 2) * 5] &&				//vertical
			checkDigged[3 + (i % 2)])					//horizontal
			putchar(' ');
		else if (checkDigged[i + (i % 2) + (i / 2) * 3] && checkDigged[3 + (i % 2)])
			putchar(200 + (i / 2) - (i % 2) * 12 - (i / 3) * 2);
		else if (checkDigged[i + (i % 2) + (i / 2) * 3] && checkDigged[1 + (i / 2) * 5])
			putchar(187 + (i % 2) * 14 + i / 2 - i / 3);
		else if (checkDigged[1 + (i / 2) * 5] && checkDigged[3 + (i % 2)])
			putchar(188 + (i % 2) * 12 - i / 2 + (i / 3) * 2);
		else if (checkDigged[1 + (i / 2) * 5])
			putchar(185 + (i % 2) * 19);
		else if (checkDigged[3 + (i % 2)])
			putchar(202 + i / 2);
	}
	return;
}

void Game::showLeaderBoard()
{
}

//////////////////////////////////////////////////////

void Game::countNumOfMines(std::pair<int, int> &currCell)//count number of mines around a cell
{
	if (cell.getMine()) {
		cell.setNumOfMines(-1);
		return;
	}
	int count = 0;

	std::pair<short, short> start, end;

	start.first = currCell.first - 1;
	start.second = currCell.second - 1;
	end.first = currCell.first + 1;
	end.second = currCell.second + 1;

	if (currCell.first == 0) start.first++;
	else if (currCell.first == _size - 1) end.first--;

	if (currCell.second == 0) start.second++;
	else if (currCell.second == _size - 1) end.second--;

	for (short i = start.second; i <= end.second; i++) {
		for (short j = start.first; j <= end.first; j++) {
			if (_cellsMap[j][i].getMine()) count++;
		}
	}

	cell.setNumOfMines(count);
}

void Game::countNumOfMinesAll()
{
	for (int i = 0; i < _size * _size; i++) {
		std::pair<int, int> currCell = { i % _size, i / _size };
		countNumOfMines(currCell);
	}
}

void Game::digCell(std::pair<int, int> &currCell)
{
	if (cell.getFlag() == FLAGGED) return;
	if (cell.getStatus() == DIGGED) return;

	cell.setStatus(DIGGED);
	_cellsDigged++;

	if (cell.getNumOfMines() == 0) {
		deleteMidLines(currCell);
		rotateJunctions(currCell);
		digNeighbor(currCell);
	}

	selectCell(currCell);
	endGameCheck(currCell);
}

void Game::digNeighbor(std::pair<int, int> &currCell) 
{
	std::pair<short, short> start, end;

	start.first = currCell.first - 1;
	start.second = currCell.second - 1;
	end.first = currCell.first + 1;
	end.second = currCell.second + 1;

	if (currCell.first == 0) start.first++;
	else if (currCell.first == _size - 1) end.first--;

	if (currCell.second == 0) start.second++;
	else if (currCell.second == _size - 1) end.second--;

	for (short i = start.second; i <= end.second; i++) {
		for (short j = start.first; j <= end.first; j++) {
			std::pair <int, int> temp = { j, i };
			
			if (_cellsMap[temp.first][temp.second].getStatus() == DIGGED) {
				if (_cellsMap[temp.first][temp.second].getNumOfMines() == 0) {
				deleteMidLines(temp);
				}
				continue;
			}
			if (_cellsMap[temp.first][temp.second].getFlag() == FLAGGED) continue;

			/*if (_cellsMap[temp.first][temp.second].getStatus() == DIGGED ||
				_cellsMap[temp.first][temp.second].getFlag() == FLAGGED) continue;*/

			_cellsMap[temp.first][temp.second].setStatus(DIGGED);
			_cellsDigged++;
			rotateJunctions(temp);
			colorCell(temp);

			if (_cellsMap[temp.first][temp.second].getNumOfMines() != 0)
				continue;
			else
				digNeighbor(temp);
			deleteMidLines(temp);
		}
	}
}

void Game::placeFlag(std::pair<int,int> &currCell) 
{
	if (cell.getStatus() == DIGGED) return;

	Common::setConsoleColor(RED, GRAY);
	Common::gotoXY(currCell.first * CELL_LENGTH + 1 + _left, currCell.second * CELL_HEIGHT + 1 + _top);
	if (cell.getFlag() == FLAGGED) {
		cell.setFlag(NOT_FLAGGED);
		_flagsPlaced--;
		std::cout << " 0 ";
		return;
	}

	Common::setConsoleColor(BLACK, LIGHT_YELLOW);
	cell.setFlag(FLAGGED);
	std::cout << " # ";
	_flagsPlaced++;
	selectCell(currCell);
}

void Game::autoFlagAndDig(std::pair<int, int> &currCell)
{
	if (cell.getNumOfMines() <= 0 || cell.getStatus() == FLAGGED) return;
	std::pair<int, int> checkDigged[8] = { {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1} };
	std::pair<short, short> start, end;

	start.first = currCell.first - 1;
	start.second = currCell.second - 1;
	end.first = currCell.first + 1;
	end.second = currCell.second + 1;

	int undugNum = 0, flagNum = 0;
	int mineNum = cell.getNumOfMines();

	if (currCell.first == 0) {
		checkDigged[0] = { -2, -2 };
		checkDigged[3] = { -2, -2 };
		checkDigged[5] = { -2, -2 };
		start.first++;
	}
	else if (currCell.first == _size - 1) {
		checkDigged[2] = { -2, -2 };
		checkDigged[4] = { -2, -2 };
		checkDigged[7] = { -2, -2 };
		end.first--;
	}

	if (currCell.second == 0) {
		checkDigged[0] = { -2, -2 };
		checkDigged[1] = { -2, -2 };
		checkDigged[2] = { -2, -2 };
		start.second++;
	}
	else if (currCell.second == _size - 1) {
		checkDigged[5] = { -2, -2 };
		checkDigged[6] = { -2, -2 };
		checkDigged[7] = { -2, -2 };
		end.second--;
	}

	int index = 0;
	std::vector<int> idx;
	std::pair<int, int> cellCheck = { -2, -2 };
	for (short i = start.second; i <= end.second; i++) {
		for (short j = start.first; j <= end.first; j++) {
			if (j == currCell.first && i == currCell.second) continue;
			if (_cellsMap[j][i].getFlag() == FLAGGED) {
				flagNum++;
			}
			else if (_cellsMap[j][i].getStatus() == NOT_DIGGED) {
				undugNum++;
				while (checkDigged[index] == cellCheck) index++;
				checkDigged[index] = { j, i };
				idx.push_back(index);
			}
			index++;
		}
	}
	
	if (undugNum == 0) return;

	//Common::gotoXY(0, 5);
	//for (int i = 0; i < 8; i++) {
	//	std::cout << checkDigged[i].first << " " << checkDigged[i].second << "     ";
	//	//if (i % 2 == 0) std::cout << '\n';
	//}
	//std::cout << '\n' << mineNum << " " << flagNum << " " << undugNum;

	if (flagNum == mineNum)
		//dig all the other cells
		while (undugNum) {
			/*Common::gotoXY(0, 7);
			std::cout << idx.back() << "D";*/
			digCell(checkDigged[idx.back()]);
			unselectCell(checkDigged[idx.back()]);
			idx.pop_back();
			undugNum--;
			//Sleep(200);
		}
	else if (undugNum  + flagNum == mineNum)
		//flag all undug cells
		while (undugNum) {
			/*Common::gotoXY(0, 7);
			std::cout << idx.back() << "F";*/
			placeFlag(checkDigged[idx.back()]);
			unselectCell(checkDigged[idx.back()]);
			idx.pop_back();
			undugNum--;
			//Sleep(200);
		}
	endGameCheck(currCell);
}

void Game::endGameCheck(std::pair<int, int> &currCell)
{
	if (_finish != 0) return;
	if (_flagsPlaced == _numOfMines && _cellsDigged == _size * _size - _numOfMines) _finish = 1;	//mark as win
	else if (cell.getMine() == HAS_MINE && cell.getStatus() == DIGGED) _finish = 2;//mark as lose
}