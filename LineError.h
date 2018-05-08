#pragma once
#include <string>
using namespace std;
struct LineError
{
	string fileName;
	string reason;
	int lineNumber;
	Piece::Player player;
	LineError(string _fileName = "kawabanga") :fileName(_fileName) {};
	LineError(string _fileName, int _lineNumber, Piece::Player _player, string _reason)
		: fileName(_fileName), reason(_reason), lineNumber(_lineNumber), player(_player)	{}
	string ToString()
	{
		return "ERROR in file " + fileName + " of player " + (player == Piece::Player::Player1 ? to_string(1) : to_string(2)) + " in line " + to_string(lineNumber) + ":\n     " + reason;
	}
};
