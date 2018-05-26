#pragma once
#include "Point.h"
#include "consoleColors.h" 
#include <sstream>

class Board;

class Piece
{
	
public:
	bool revealed;
	enum DefendResult { Alive, Dead };
	enum Player { Player1, Player2 };
protected:
	bool alive = true;
	Board* gameBoard;
	Player player;
	Point position;
public:
	bool IsAlive();

	Point GetPosition();

	Player GetPlayer();

	Piece(Point _position, Player _player,Board* _game) : position(_position), player(_player),gameBoard(_game) {};
	virtual DefendResult Defend(Piece * enemy) = 0;
	virtual char ToChar() = 0;
	virtual string ToString() = 0;
	virtual void Die();
	Board* getBoardFromPiece();
};

