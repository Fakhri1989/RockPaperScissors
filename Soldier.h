#pragma once
#include "Movable.h"

class Soldier : public Movable
{

public:
	enum Type { R, P, S };
	Type type;
	Soldier(Point _pos, Player _player, Type _type): Movable(_pos, _player), type(_type){}
	virtual Piece::DefendResult Defend(Piece * enemy) override;
	virtual char ToChar() override;
	virtual string ToString() override;
};
