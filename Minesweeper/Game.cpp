#include "Game.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::setUpGame(int size) {
	Common().setFontInfo(18, 18);
	Common::clearConsole();
	drawGame(size);
}

void Game::drawGame(int size) {//vẽ ra bảng game
	int left = 0, top = 0;
	drawHorizontalLine(size,left, top);
	drawVerticalLine(size, left, top);
	drawCorner(size, left, top);
	Sleep(50000);
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