#include <iostream>
#include "Common.h"
#include "Menu.h"


int main()
{
	Menu test;
	test.renderMainScreen();

	Sleep(5000);
	Common::clearConsole();
}