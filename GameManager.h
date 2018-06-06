#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Board.h"
#include "Gotoxy.h"
#include "LineError.h"
using namespace std;

class GameManager {

protected:
	Board gameBoard;
	bool show1 = false;
	bool show2 = false;
	string parsePlacement(string input, Piece::Player player);
public:

	GameManager() {};

	void setBoard(int length, int width);

	Board* getBoard() { return &gameBoard; };

	bool contains(string s, char ch);

	int stoi(string in);

	bool isDigit(char ch);

	bool isItKnown(Piece::Player player);

	int checkIfDistanceOk(int x0, int y0, int x1, int  y1);
	void Kill(Piece *First, Piece *Second);
	void killOne(Piece *moi);
};
