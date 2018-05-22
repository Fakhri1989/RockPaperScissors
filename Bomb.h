#pragma once
#include "Piece.h"

class Bomb : public Piece {

public:

	Bomb(Point _pos, Player _player, Board* gameBoard):Piece(_pos, _player,gameBoard) {};
	virtual Piece::DefendResult Defend(Piece * enemy) override;
	virtual char ToChar() override;
	virtual string ToString() override;

};