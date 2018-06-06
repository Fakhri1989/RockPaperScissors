#pragma once
#include "Piece.h"
#include <string>
#include <list>

using namespace std;

class Playa {
	static int player1;
	static int player2;
	
	int Player;
	string name;
public:
	Playa(int who); 
	void operator<< (string in) { name = in; };
	string getPlayerNAme() { return name; };
};