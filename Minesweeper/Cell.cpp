#include "Cell.h"

bool Cells::getMine()
{
	return _hasMine;
}

bool Cells::getStatus()
{
	return _status;
}

int Cells::getNumOfMines()
{
	return _numOfMinesAround;
}

bool Cells::getFlag()
{
	return _flag;
}

void Cells::setStatus(bool status)
{
	_status = status;
}

void Cells::setMine(bool mine)
{
	_hasMine = mine;
}

void Cells::setNumOfMines(int n)
{
	_numOfMinesAround = n;
}

void Cells::setFlag(bool flag)
{
	_flag = flag;
}
