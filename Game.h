#pragma once
#include "GameManager.h"
#include "FVF.h"
#include "PVP.h"

class Game {
	int mode;
public:
	Game(char** argv, int argc);
	string argvToString(char** argv, int argc);
	bool isConsole(string target);
};