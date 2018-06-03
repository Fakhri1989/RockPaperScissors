#include "Flag.h"

Piece::DefendResult Flag::Defend(Piece * enemy)
{
	this->Die();
	enemy->revealed = true;
	return Piece::DefendResult::Dead;
}

char Flag::ToChar(bool show)
{
	if (revealed)
		return 'F';
	else if (show && !revealed)
		return 'U';
}

char Flag::pieceInfo()
{
	return 'F';
}

string Flag::ToString()
{
	return "Flag";
}
