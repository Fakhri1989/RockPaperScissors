#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Board.h"
#include "Flag.h"
#include "Gotoxy.h"
#include "LineError.h"
using namespace std;

class GameManager {
protected:
	bool show1 = false;
	bool show2 = false;
public:
	virtual int run(string) = 0;

	//void modeSelector(char** argv, int argc);

	bool contains(string s, char ch);

	int stoi(string in);

	//string extractOneArg(char* word, int &i);

	bool isDigit(char ch);

	bool isItKnown(Piece::Player player);

	int checkIfDistanceOk(int x0, int y0, int x1, int  y1);
};