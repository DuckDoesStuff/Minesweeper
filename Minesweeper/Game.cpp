﻿#include "Game.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::setUpGame(int size) {
	Common().setFontInfo(13,13);
	Common::clearConsole();
	drawGame(size);
}

void Game::drawGame(int size) {//vẽ ra bảng game
	int left = 0, top = 0;

	Common::gotoXY(left, top);
	for (int i = 0; i <= CELL_HEIGHT * size; i+= CELL_HEIGHT) {
		Common().gotoXY(left, top + i);
		for (int j = 0; j <= CELL_LENGTH * size; j++) {
			putchar(205);
		}
	}
	
	Common().gotoXY(left, top); //  tren ben trai
	putchar(201);

	for (int i = 1; i < CELL_HEIGHT * size; i++) {
		Common().gotoXY(left, top+i);
		putchar(186);
	}
	Common().gotoXY(left,top + CELL_HEIGHT * size); // duoi ben trai
	putchar(200);
	
	Common().gotoXY(left + CELL_LENGTH * size ,top + CELL_HEIGHT * size); // duoi ben phai
	putchar(188);

	for (int i = 1; i < CELL_HEIGHT * size; i++) {
		Common().gotoXY(left + CELL_LENGTH * size, top+i);
		putchar(186);
	}

	Common().gotoXY(left + CELL_LENGTH * size, top); // tren ben phai
	putchar(187);
	Sleep(50000);
	
}