#pragma once
#include "Movable.h"

class Soldier : public Movable
{

public:
	enum Type { R, P, S };
private:
	Type type;
public:
	Soldier(Point _pos, Player _player, Type _type)
		: Movable(_pos, _player), type(_type)
	{

	}
	Piece::DefendResult Defend(Piece * enemy) override
	{
		board.RemovePiece(this);
		return Piece::DefendResult::Dead;
	}
};
