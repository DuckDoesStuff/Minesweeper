#pragma once

#include <iostream>
#include "Common.h"
#include <string>

class Cells {
private:

	bool _hasMine = 0;
	bool _status = 1;		//1: NORMAL, 0: DUG
	int _numOfMinesAround = 0;

public:

	bool getStatus();
	bool getMine();
	int getNumOfMines();

	void setStatus(bool);
	void setMine(bool);
	void setNumOfMines(int);
};