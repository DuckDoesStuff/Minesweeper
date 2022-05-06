#pragma once

#include <iostream>
#include "Common.h"
#include <string>

#define NOT_DIGGED 1
#define DIGGED 0

#define HAS_MINE 1
#define NOT_MINE 0

#define FLAGGED 1
#define NOT_FLAGGED 0

class Cells {
private:

	bool _hasMine = NOT_MINE;
	bool _status = NOT_DIGGED;		//1: NOT DIGGED, 0: DIGGED
	bool _flag = NOT_FLAGGED;		//0: NOT FLAGGED, 1: FLAGGED
	int _numOfMinesAround = -2;

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