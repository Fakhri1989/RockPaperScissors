#pragma once
#include "GameManager.h"
#define REG "kawabanga"

class FVF : public GameManager
{
	bool delay = false;
	int delayTime = 50;
	bool quiet = false;
	bool onlyKnownInfo = false;

	std::string parameters;

public:
	FVF(string _parameters);
	int run(string);
	int getInfoFromLine(string str, int& x, int& y, int& nx, int&  ny, int& jx, int& jy, char & jt);
	bool updateParameters(string update);
	bool changeTheOthers(string parameter);
	bool changeDelay(int time);

	void operator++() { onlyKnownInfo = true; };
	void operator--() { quiet = true; };

	bool catchFirstNum(string str, int& x, int& index);
	LineError parsePlacementFile(string path, Piece::Player player);
	LineError parseMoveFile(string player1File, string player2File, int & winner, string & reason);
	string parseMove(string input, Piece::Player player);
};
