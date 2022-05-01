#include "Game.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::setUpGame(int size) {
	Common::clearConsole();
	drawGame(size);
}

void Game::drawGame(int size) {//vẽ ra bảng game
	int left = 0, top = 0;

	Common::gotoXY(left, top);
	for (int i = 0; i < CELL_LENGTH * size; i++) {
		std::cout << "\n";
		for (int j = 0; j < CELL_HEIGHT * size; j++) {
			putchar(205);
		}
	}
	
	Common().gotoXY(left, top + 1); //  tren ben trai
	putchar(201);
	top+=2;
	for (top; top < CELL_HEIGHT * size; top++) {
		Common().gotoXY(left, top);
		putchar(186);
	}
	Common().gotoXY(left , top); // duoi ben trai
	putchar(200);
	

	left = CELL_LENGTH * size;
	Common().gotoXY(top,left); // duoi ben phai
	putchar(188);
	top--;
	for (top; top > 0; top--) {
		Common().gotoXY(left, top);
		putchar(186);
	}
	Common().gotoXY(left, top+1); // tren ben phai
	putchar(187);
	Sleep(5000);
	
}