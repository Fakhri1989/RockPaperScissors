#pragma once
#include <string>
#include<iostream>
#include"GameManager.h"
using namespace std;
enum Mode { MOVE, PLACE, START };
enum Comunicate{NAME,SIZE,NUMBER};
class PVP : public GameManager{

public:
	int run();
	void clearString(string& data) { data = ""; };
	string TalkToPlayer(Mode mode);
	void setBoardSize(int length, int height);
	string pieceModifier(string data, Mode mode);
	void boardSetter(string raw);
	bool wannadefaults(Comunicate mode);

};