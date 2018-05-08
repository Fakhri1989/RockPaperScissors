#pragma once
#include "Piece.h"
#include <string>
#include <list>
using namespace std;

class Playa /*big Pimpin*/{
	static int player1;
	static int player2;
	
	int Player;
	string name;
public:
	Playa(int who) :Player(who) { if (who == 1) name = "Player One"; else name = "Player Two"; };
	void setPlayerName(string _name) { name = _name; };
	string getPlayerNAme() { return name; };
};