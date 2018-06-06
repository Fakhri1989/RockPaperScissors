#pragma once
#include "Piece.h"
#include "Flag.h"
#include "Bomb.h"
#include "Soldier.h"
#include "Joker.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <list>
#include <stdlib.h>
#include "consoleColors.h"
#include "Counter.h"
#include "Player.h"
using namespace std;

class GameManager;

class Board {
private:
	Counter one, two;
	Piece *** board;
	int height;
	int width;
	list <Piece *>pieces;
protected:
	Playa PlayerOne, PlayerTwo;
public:
	Board():PlayerOne(1),PlayerTwo(2) {};
	int getHeight() { return height; };
	void setCounters(Counter PlayerOneCounter, Counter playerTwoCounter);

	void setBoard(int _height, int _width);
	
	list<Piece *> getList() { return pieces;};
	
	void operator ()(Piece *p) { pieces.push_back(p); };

	Piece * getPiece(Point pos);

	Playa getPlayerOne() { return PlayerOne; };

	Playa getPlayerTwo() { return PlayerTwo; };

	string PlacePiece(Piece * piece, bool seeMe, GameManager *game);

	void RemovePiece(Piece * piece);

	void PrintWhileWePlay(Point first, Point second,int delay,bool);

	void PrintHelper(Point loc, bool info,color paint);

	void MovePiece(Piece * piece, Point newPos);

	~Board();

	string ToString();

	void printBoard(bool show1,bool show2,int delay,bool knownInfo);

	Counter & GetPlayerOneCounter() { return one; }

	Counter & GetPlayerTwoCounter() { return two; }

	enum GAME_STATUS {KEEP_PLAYING,  TIE , PLAYER_1_WIN, PLAYER_2_WIN };
	
	GAME_STATUS checkStatus(string & reason);

	Piece* operator[] (Point pos) { return board[pos.i][pos.j]; };

	friend void Piece::Die();

	void PrintChanges(bool show1, bool show2,bool knownInfo);
	
	list <Joker *> getJokers(Piece::Player player);
};
