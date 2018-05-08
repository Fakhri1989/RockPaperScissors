#pragma once
#include "Piece.h"
#include "Board.h"

class Flag : public Piece
{
public:
	Flag(Point _pos, Player _player)
		: Piece(_pos, _player)
	{

	}
	Piece::DefendResult Defend(Piece * enemy) override;
	virtual char ToChar() override;
	virtual string ToString() override;
};
