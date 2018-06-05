#pragma once
#include "Piece.h"

class Counter {
	int maxRocks, MaxPapers,maxScissors, maxBombs, maxFlags, maxJokers;
	int rock = 0;
	int paper = 0;
	int scissors = 0;
	int joker = 0;
	int bomb = 0;
	int flag = 0;
public:


	Counter(int _rock = 2, int _paper = 5, int _scissors = 1, int _joker = 2, int _bomb = 2, int _flag = 1 )
		:maxRocks(_rock), MaxPapers(_paper), maxScissors(_scissors), maxJokers(_joker), maxBombs(_bomb), maxFlags(_flag) {}

	string checkCounter(Piece * piece);

	bool isFull()
	{
		return rock == maxRocks && paper == MaxPapers && scissors == maxScissors && bomb == maxBombs && flag == maxFlags && joker == maxJokers;
	}


};
