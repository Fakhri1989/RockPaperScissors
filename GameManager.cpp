#include "GameManager.h"
#include "Board.h"
#include "consoleColors.h"

using namespace std;

void GameManager::setBoard(int length, int width)
{
	gameBoard.setBoard(length, width);
}

string GameManager::parsePlacement(string input, Piece::Player player)
{
	Bomb * bomb;
	Flag * flag;
	Soldier * sol;
	int y0, x0;
	char c0, c1;


	if (sscanf(input.c_str(), "%c %d %d", &c0, &x0, &y0) == 3)
	{
		switch (c0)
		{
		case 'B':
			bomb = new Bomb(Point(x0, y0), player, getBoard());
			return getBoard()->PlacePiece(bomb, isItKnown(player), this);
			break;
		case 'F':
			flag = new Flag(Point(x0, y0), player, getBoard());
			return getBoard()->PlacePiece(flag, isItKnown(player), this);
			break;
		case 'R':
			sol = new Soldier(Point(x0, y0), player, Soldier::Type::R, getBoard());
			return getBoard()->PlacePiece(sol, isItKnown(player), this);
			break;
		case 'S':
			sol = new Soldier(Point(x0, y0), player, Soldier::Type::S, getBoard());
			return getBoard()->PlacePiece(sol, isItKnown(player), this);
			break;
		case 'P':
			sol = new Soldier(Point(x0, y0), player, Soldier::Type::P, getBoard());
			return getBoard()->PlacePiece(sol, isItKnown(player), this);
			break;
		case 'J':
			Joker * joker;
			if (sscanf(input.c_str(), "%c %d %d %c", &c0, &x0, &y0, &c1) == 4)
			{
				switch (c1)
				{
				case 'R':
					joker = new Joker(Point(x0, y0), player, Joker::ID::R, getBoard());
					return getBoard()->PlacePiece(joker, 1, this);
					break;
				case 'P':
					joker = new Joker(Point(x0, y0), player, Joker::ID::P, getBoard());
					return getBoard()->PlacePiece(joker, isItKnown(player), this);
					break;
				case 'S':
					joker = new Joker(Point(x0, y0), player, Joker::ID::S, getBoard());
					return getBoard()->PlacePiece(joker, isItKnown(player), this);
					break;
				case 'B':
					joker = new Joker(Point(x0, y0), player, Joker::ID::B, getBoard());
					return getBoard()->PlacePiece(joker, isItKnown(player), this);
					break;
				default:
					return "Bad input- wrong type for Joker";
					break;
				}
			}
			else
				return "No Joker type was given";
			break;
		default:
			return "Bad format- no piece type by this name";
			break;
		}
	}
	else
		return "input does not meet criteria. only <PIECE_CHAR> <X> <Y> or J <X> <Y> <PIECE_CHAR> is allowed.";
}

bool GameManager::contains(string s, char ch)
{
	return s.find(ch) != string::npos;
}

int GameManager::stoi(string in)
{
	int j = 0;
	int res = 0;
	for(int i=in.length()-1 ;i>=0;i--)
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
