#include "Menu.h"


Menu::Menu() {

}

Menu::~Menu() {

}

void Menu::renderMainScreen()
{
	Common::setupConsole(18, BLACK, BRIGHT_WHITE);
	Common::clearConsole();
	printTitle();
	renderOptionsBox();
	renderOptionsText();
	renderCurOpt();
}

void Menu::printTitle()
{
	std::ifstream in("Titles\\Minesweeper.txt");

	Common().setConsoleColor(BLACK, RED);

	int left = 11, top = 2;
	int i = 0;
	while (!in.eof())
	{
		std::string s;
		getline(in, s);
		Common::gotoXY(left, top + i);
		std::cout << s;
		i++;
		Sleep(20);
	}
	in.close();
}

void Menu::renderOptionsBox()
{
	int left = 57, top = 17;
	int boxW = 21, boxH = 2;

	Common::setConsoleColor(BLACK, BRIGHT_WHITE);

	int box;
	for (int i = 0; i < Menu()._opt; i++) {
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
	Common::gotoXY(left, top + boxH*Menu()._opt);
	putchar(200);
	Common::gotoXY(left + boxW, top + boxH*Menu()._opt);
	putchar(188);
}

void Menu::renderOptionsText()
{
	int left = 48, top = 18;
	int width = 41;
	for (int i = 0; i < Menu()._opt; i++) {
		Common::gotoXY((width - Menu()._selections[i].length())/2 + left, top + i*2);
		std::cout << Menu()._selections[i];
	}
}

void Menu::renderCurOpt()
{
	int left1 = 54, top = 18;
	Common::gotoXY(left1, top);
	putchar(62);				//left arrows
	putchar(62);
	int left2 = 80;
	Common::gotoXY(left2, top); 
	putchar(60);				//right arrows
	putchar(60);
	int c;
	while (true) {
		c = Common::getConsoleInput();
		switch (c) {
			case 2: {			//move up
				Common::gotoXY(left1, top);
				putchar(' ');
				putchar(' ');
				Common::gotoXY(left2, top);
				putchar(' ');
				putchar(' ');
				top -= 2;
				Common::gotoXY(left1, top);
				putchar(62);
				putchar(62);
				Common::gotoXY(left2, top);
				putchar(60);
				putchar(60);
				break;
			}
			case 5: {			//move down
				Common::gotoXY(left1, top);
				putchar(' ');
				putchar(' ');
				Common::gotoXY(left2, top);
				putchar(' ');
				putchar(' ');
				top += 2;
				Common::gotoXY(left1, top);
				putchar(62);
				putchar(62);
				Common::gotoXY(left2, top);
				putchar(60);
				putchar(60);
			}
			case 6: {			//enter

			}
		
		}
	}
}