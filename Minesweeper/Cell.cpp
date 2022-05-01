#include "Cell.h"

bool Cells::getMine()
{
	return _hasMine;
}

int Cells::getStatus()
{
	return _status;
}

int Cells::getNumOfMines()
{
	return _numOfMinesAround;
}

void Cells::setStatus(int status)
{
	_status = status;
}

void Cells::setMine(bool mine)
{
	_hasMine = mine;
}

void Cells::countNumOfMines(Cells** cell)
{
	return;
}