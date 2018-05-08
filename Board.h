#pragma once
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

class Board {
private:
	Counter one, two;
	Piece *** board;
	Playa PlayerOne,PlayerTwo;
	int height;
	int width;
	list <Piece *>pieces;
public:
	Board(int _height, int _width);

	Piece * getPiece(Point pos);

	string PlacePiece(Piece * piece, bool seeMe);

	void RemovePiece(Piece * piece);

	void PrintWhileWePlay(Point first, Point second,int delay);

	void MovePiece(Piece * piece, Point newPos);

	~Board();

	string ToString();

	void printBoard(bool show1,bool show2,int delay);

	enum GAME_STATUS {KEEP_PLAYING,  TIE , PLAYER_1_WIN, PLAYER_2_WIN };

	GAME_STATUS checkStatus(string & reason);

};
extern Board board;
