#include "GameManager.h"
#include "Board.h"
#include "consoleColors.h"

using namespace std;
//Board board(10, 10);

void GameManager::setBoard(int length, int width)
{
	gameBoard.setBoard(length, width);
}

bool GameManager::contains(string s, char ch)
{
	return s.find(ch) != string::npos;
}

int GameManager::stoi(string in)
{
	int j = 0;
	int res = 0;
	for(int i=in.length()-1;i>=0;i--)
	{
		res += (in[i] - '0')*pow(10, j);
		j++;
	}
	return res;
}

bool GameManager::isDigit(char ch)
{return ch >= '0' && ch <= '9';
}

bool GameManager::isItKnown(Piece::Player player)
{
	if (player == 1)
		return show1;
	return show2;
}

int GameManager::checkIfDistanceOk(int x0, int y0, int x1, int y1)
{
	if (x0 - x1 == 1 || x0 - x1 == -1)
	{
		if (y1 == y0)
			return 1;
	}
	else if (y1 - y0 == 1 || 1 - y0 == 1)
	{
		if (x1 == x0)
			return 1;
	}

	return 0;
}

void GameManager::Kill(Piece * First, Piece * Second)
{
		killOne(First);
		killOne(Second);
}

void GameManager::killOne(Piece * moi)
{
	if (!(moi->IsAlive()))
	{
		getBoard()->RemovePiece(moi);
	}
}
