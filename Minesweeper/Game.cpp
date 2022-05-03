#include "Game.h"
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

	int c = 0;
	int count = 0;
	bool win = false;
	bool lose = false;

	while (!win && !lose) {
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
			if (_cellsMap[currCell.first][currCell.second].getFlag()) break;
			if (_cellsMap[currCell.first][currCell.second].getMine()) lose = true;	//Lost when steps on mine
			digCell(currCell);
			//deleteMidLines();
			break;
		case 8:							//K, k(flag)
			placeFlag(currCell);
			break;
		default:break;
		}
		win = endGameCheck();
	}

	//xu ly sau khi ket thuc 1 van game
	if (win) winScreen();
	else if (lose)
	{
		tryAgain();
		c = Common::getConsoleInput();
		if (c == 6) playGame(size);
	}
}

void Game::setupGame() {
	Common::setConsoleColor(BLACK, BRIGHT_WHITE);
	Common::clearConsole();
	generateGameData();
	drawGame();
	//renderGameData(); 
}

void Game::generateGameData()
{
	generateNumOfMines();
	generateMines();
	_flagsPlaced = 0;
	_cellsDigged = 0;
}

void Game::generateNumOfMines()
{
	switch (_size)
	{
	case 10:
		_numOfMines = 5;
		break;
	case 15:
		_numOfMines = 10;
		break;
	case 25:
		_numOfMines = 100;
	default:
		break;
	}
}

void Game::generateMines()
{
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
	int left = 2, top = 1;
	for (int i = 0; i < _size * CELL_HEIGHT; i += CELL_HEIGHT) {
		for (int j = 0; j < _size * CELL_LENGTH; j += CELL_LENGTH) {
			Common::gotoXY(left + j, top + i);
			std::cout << _cellsMap[j / CELL_LENGTH][i / CELL_HEIGHT].getMine();
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
	if (_cellsMap[currCell.first][currCell.second].getFlag()) {		//show flag
		Common::gotoXY(x + 2, y);
		putchar(35);
		return;
	}
	if (_cellsMap[currCell.first][currCell.second].getStatus()) {	//show undug cell
		Common::setConsoleColor(RED, GRAY);	
		Common::gotoXY(x + 2, y);
		putchar('0');
		return;
	}

	if (_cellsMap[currCell.first][currCell.second].getNumOfMines() != 0) {
		Common::gotoXY(x + 2, y);
		std::cout << _cellsMap[currCell.first][currCell.second].getNumOfMines();
	}

}

void Game::colorCell(std::pair<int, int> &currCell)
{
	int x = _left + currCell.first * CELL_LENGTH + 2;
	int y = _top + currCell.second * CELL_HEIGHT + 1;
	Common::gotoXY(x, y);

	if (_cellsMap[currCell.first][currCell.second].getFlag()) {
		Common::setConsoleColor(BLACK, LIGHT_PURPLE);
		putchar(35);
		return;
	}

	if (_cellsMap[currCell.first][currCell.second].getStatus()) {
		Common::setConsoleColor(BLACK, GRAY);
		putchar('0');
		return;
	}
	else {
		Common::setConsoleColor(BLACK, BLACK);
		putchar(' ');
	}

	Common::gotoXY(x, y);

	int num = _cellsMap[currCell.first][currCell.second].getNumOfMines();
	if (!num) return;

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
	bool L = 0, R = 0, T = 0, B = 0;

	//Left cell
	if (currCell.first != 0) {
		tmp = { currCell.first - 1, currCell.second };
		x = _left + tmp.first * CELL_LENGTH + 4;
		y = _top + tmp.second * CELL_HEIGHT;
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 0 &&
			_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0) {
			Common::gotoXY(x, y + 1);
			putchar(' ');
			Common::gotoXY(x, y);
			if (tmp.second == 0)
				putchar(205);
			L = 1;
		}
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 1) L = 1;
	}

	//Right cell
	if (currCell.first != _size - 1) {
		tmp = { currCell.first + 1, currCell.second };
		x = _left + tmp.first * CELL_LENGTH;
		y = _top + tmp.second * CELL_HEIGHT;
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 0 &&
			_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0) {
			Common::gotoXY(x, y + 1);
			putchar(' ');
			Common::gotoXY(x, y + 2);
			if (tmp.second == _size - 1)
				putchar(205);
			R = 1;
		}
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 1) R = 1;
	}

	//Top cell
	if (currCell.second != 0) {
		tmp = { currCell.first, currCell.second - 1 };
		x = _left + tmp.first * CELL_LENGTH;
		y = _top + tmp.second * CELL_HEIGHT + 2;
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 0 &&
			_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0) {
			Common::gotoXY(x + 1,y);
			std::cout << "   ";
			Common::gotoXY(x ,y);
			if (tmp.first == 0)
				putchar(186);
			T = 1;
		}
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 1) T = 1;
	}

	//Bottom cell
	if (currCell.second != _size - 1) {
		tmp = { currCell.first, currCell.second + 1 };
		x = _left + tmp.first * CELL_LENGTH;
		y = _top + tmp.second * CELL_HEIGHT;
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 0 &&
			_cellsMap[tmp.first][tmp.second].getNumOfMines() == 0) {
			Common::gotoXY(x + 1, y);
			std::cout << "   ";
			Common::gotoXY(x + 4, y);
			if (tmp.first == _size - 1)
				putchar(186);
			B = 1;
		}
		if (_cellsMap[tmp.first][tmp.second].getStatus() == 1) B = 1;
	}
	
	if (currCell.first == 0 || currCell.first == _size - 1 || currCell.second == 0 || currCell.second == _size - 1) return;

	x = _left + currCell.first * CELL_LENGTH;
	y = _top + currCell.second * CELL_HEIGHT;

	if (L) {
		Common::gotoXY(x, y);
		if (T) putchar(188);
		else putchar(185);

		Common::gotoXY(x, y + 2);
		if (B) putchar(187);
		else putchar(185);
	}
	else {
		Common::gotoXY(x, y);
		putchar(185);
		Common::gotoXY(x, y + 2);
		putchar(185);
	}

	if (R) {
		Common::gotoXY(x + 4, y);
		if (T) putchar(200);
		else putchar(202);

		Common::gotoXY(x + 4, y + 2);
		if (B) putchar(201);
		else putchar(202);
	}
	else {
		Common::gotoXY(x + 4, y);
		putchar(204);
		Common::gotoXY(x + 4, y + 2);
		putchar(204);
	}
	Sleep(1500);
}

//////////////////////////////////////////////////////

void Game::countNumOfMines(std::pair<int, int> &currCell)//count number of mines around a cell
{
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

	_cellsMap[currCell.first][currCell.second].setNumOfMines(count);
}

void Game::digCell(std::pair<int, int>& currCell)
{
	
	if (cell.getStatus() == 0) return;

	countNumOfMines(currCell);
	cell.setStatus(0);
	_cellsDigged++;

	if (cell.getNumOfMines() == 0)
		digNeighbor(currCell);
	  
	selectCell(currCell);
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
			if (_cellsMap[temp.first][temp.second].getStatus() == 0 || //if cell has been dug or have mines then continue
				_cellsMap[temp.first][temp.second].getMine() == 1) continue;

			countNumOfMines(temp);
			_cellsMap[temp.first][temp.second].setStatus(0);
			_cellsDigged++;
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
	if (!_cellsMap[currCell.first][currCell.second].getStatus()) return;

	Common::gotoXY(currCell.first * CELL_LENGTH + 1 + _left, currCell.second * CELL_HEIGHT + 1 + _top);
	if (_cellsMap[currCell.first][currCell.second].getFlag()) {
		_cellsMap[currCell.first][currCell.second].setFlag(0);
		_flagsPlaced--;
		std::cout << " 0 ";
		return;
	}

	Common::setConsoleColor(BLACK, LIGHT_PURPLE);
	_cellsMap[currCell.first][currCell.second].setFlag(1);
	std::cout << " # ";
	_flagsPlaced++;
	selectCell(currCell);
}

bool Game::endGameCheck()
{
	return (_flagsPlaced == _numOfMines && _cellsDigged == _size * _size - _numOfMines);
}
