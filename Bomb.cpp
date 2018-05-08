#include "Bomb.h"

Piece::DefendResult Bomb::Defend(Piece * enemy)
{
	if (enemy != nullptr)
		enemy->Die();
	this->Die();

	return Piece::DefendResult::Dead;
}

char Bomb::ToChar()
{
	return 'B';
}

string Bomb::ToString()
{
	return "Bomb";
}
