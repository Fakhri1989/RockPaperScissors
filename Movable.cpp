#include "Movable.h"
#include "Board.h"

void Movable::Move(Point newPos)
{
	(getBoardFromPiece())->MovePiece(this, newPos);
	position = newPos;
}

void Movable::Attack(Piece * enemy)
{
	if (enemy->Defend(this) == Piece::DefendResult::Dead && this->alive)
	{
		Move(enemy->GetPosition());
	}
	else if (enemy->Defend(this) == Piece::DefendResult::Dead && this->Dead)
	{
		enemy->Die();
		this->Die();
	}
	else
	{
		this->Die();
	}
}
