#pragma once
#include "Piece.h"
class Movable : public Piece
{
protected:
	void Move(Point newPos);
public:

	Movable(Point _position, Player _player): Piece(_position, _player){}

	virtual void Attack(Piece * enemy);
};