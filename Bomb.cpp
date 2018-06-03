#include "Bomb.h"

Piece::DefendResult Bomb::Defend(Piece * enemy)
{
	if (enemy != nullptr)
		enemy->Die();
	this->Die();

	return Piece::DefendResult::Dead;
}

char Bomb::ToChar(bool show)
{
	if (show)
		return 'U';
	return 'B';
}

char Bomb::pieceInfo()
{
	return 'B';
}

string Bomb::ToString()
{
	return "Bomb";
}
