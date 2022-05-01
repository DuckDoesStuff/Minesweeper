#pragma once

#include <iostream>
#include "Common.h"
#include <string>

class Cells {
private:
	bool _hasMine = 0;
	int _status = 0;		//0: NORMAL, -1: DUG
	int _numOfMinesAround = 0;
public:
	void countNumOfMines(Cells**);

};