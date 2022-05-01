#pragma once

#include <iostream>
#include "Common.h"
#include <string>

class Cells {
private:

	bool _hasMine = 0;
	int _status = 1;		//1: NORMAL, -1: DUG
	int _numOfMinesAround = 0;

public:

	int getStatus();
	bool getMine();
	int getNumOfMines();

	void setStatus(int);
	void setMine(bool);

	void countNumOfMines(Cells**);
};