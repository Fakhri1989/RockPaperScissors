#include "Piece.h"


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
}

Board * Piece::getBoardFromPiece()
{
	return gameBoard;
}
