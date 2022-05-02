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