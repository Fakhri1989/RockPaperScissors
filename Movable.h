#pragma once
#include "Piece.h"
class GameManager;
class Movable : public Piece
{
	
public:
	void Move(Point newPos);
	virtual DefendResult Defend(Piece * enemy) override = 0;
	Movable(Point _pos, Player _player, Board* gameBoard) :Piece(_pos, _player, gameBoard) {};
	virtual string ToString() = 0;
	virtual void Attack(Piece * enemy);
	virtual char ToChar(bool show) override = 0 ;

};