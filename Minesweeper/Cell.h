#pragma once

#include <iostream>
#include "Common.h"
#include <string>

class Cells {
private:

	bool _hasMine = 0;
	bool _status = 1;		//1: NORMAL, 0: DUG
	bool _flag = 0;			//0: NOT FLAGGED, 1: FLAGGED
	int _numOfMinesAround = 0;

public:

	bool getStatus();
	bool getMine();
	int getNumOfMines();
	bool getFlag();

	void setStatus(bool);
	void setMine(bool);
	void setNumOfMines(int);
	void setFlag(bool);
};