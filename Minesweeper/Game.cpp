#include "Game.h"

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
		putchar(205);
	}
}