#include "Piece.h"
#include "Board.h"

bool Piece::IsAlive()
{
	return alive;
}

Point Piece::GetPosition()
{
	return position;
}

Piece::Player Piece::GetPlayer()
{
	return player;
}

void Piece::Die()
{
	alive = false;
	board.RemovePiece(this);
}
