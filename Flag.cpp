#include "Flag.h"

Piece::DefendResult Flag::Defend(Piece * enemy)
{
	this->Die();
	return Piece::DefendResult::Dead;
}

char Flag::ToChar()
{
	return 'F';
}

string Flag::ToString()
{
	return "Flag";
}
