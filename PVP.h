#pragma once
#include <string>
#include "PVP.h"
#include "Piece.h"
#include "GameManager.h"

class PVP : public GameManager{
private:
	int height, width;
public:
	PVP() {

	}
	void run();
	string parseMove(int x0, int y0, int x1, int y1, Piece::Player player);
	string parseJoker(int jx, int jy, char c, Piece::Player player);
};
