#include "Menu.h"

void Menu::renderMainScreen()
{
	Common::setupConsole(15, BLACK, BRIGHT_WHITE);
	Common::clearConsole();
	printTitle();
	renderOptionsBox();
}

void Menu::printTitle()
{
	std::ifstream in("Titles\\Minesweeper.txt");

	Common::setConsoleColor(BLACK, RED);

	int left = 25, top = 3;
	int i = 0;
	while (!in.eof())
	{
		std::string s;
		getline(in, s);
		Common::gotoXY(left, top + i);
		std::cout << s;
		i++;
		//Sleep(10);
	}
	in.close();
}

void Menu::renderOptionsBox()
{
	int left = 69, top = 19;
	int boxW = 25, boxH = 3;

	Common::setConsoleColor(BLACK, BRIGHT_WHITE);

	int box;
	for (int i = 0; i < _opt; i++) {
		box = i * boxH;
		for (int j = 0; j < boxW; j++) {
			Common::gotoXY(left + j, top + box);	
			putchar(205);
			Common::gotoXY(left + j, top + boxH + box);
			putchar(205);
		}

		for (int j = 0; j < boxH; j++) {
			Common::gotoXY(left, top + j + box);
			putchar(186);
			Common::gotoXY(left + boxW, top + j + box);
			putchar(186);
		}

		Common::gotoXY(left, top + box);
		putchar(204);
		Common::gotoXY(left + boxW, top + box);
		putchar(185);
		Common::gotoXY(left, top + boxH + box);
		putchar(204);
		Common::gotoXY(left + boxW, top + boxH + box);
		putchar(185);
	}
	Common::gotoXY(left, top);
	putchar(201);
	Common::gotoXY(left + boxW, top);
	putchar(187);
	Common::gotoXY(left, top + boxH*_opt);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH*_opt);
	putchar(188);
}