#pragma once
#include "Piece.h"

class Counter {
	enum MaxPieces { ROCK = 2, PAPER = 5, SCISSORS = 1, BOMB = 2, JOKER = 2, FLAG = 1 };
public:
	int rock;
	int paper;
	int scissors;
	int joker;
	int bomb;
	int flag;

	Counter(int _rock = 0, int _paper = 0, int _scissors = 0, int _joker = 0, int _bomb = 0, int _flag = 0)
		:rock(_rock), paper(_paper), scissors(_scissors), joker(_joker), bomb(_bomb), flag(_flag) {}

	string checkCounter(Piece * piece);
	void LowerCounter(char target);
}
