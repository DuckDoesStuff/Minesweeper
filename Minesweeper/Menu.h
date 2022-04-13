#pragma once

#include "Common.h"
#include <fstream>
#include <string>
#include <iostream>

class Menu {
private:
	static const int _opt = 5;			//number of options
public:
	static void renderMainScreen();
	static void printTitle();
	static void renderOptionsBox();
};
