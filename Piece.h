#pragma once
#include "Point.h"
#include "consoleColors.h" 
#include <sstream>

class Piece
{
	
public:
	bool revealed;
	enum DefendResult { Alive, Dead };
	enum Player { Player1, Player2 };
protected:
	bool alive = true;
	Player player;
	Point position;
public:
	bool IsAlive();

	Point GetPosition();

	Player GetPlayer();

	Piece(Point _position,Player _player ): position(_position), player(_player){}
	virtual DefendResult Defend(Piece * enemy) = 0;
	virtual char ToChar() = 0;
	virtual string ToString() = 0;
	virtual void Die();
	
	
};

