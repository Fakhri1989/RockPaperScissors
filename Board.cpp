#include "Board.h"
#include "Flag.h"
#include "Gotoxy.h"

void Board::setCounters(Counter PlayerOneCounter, Counter playerTwoCounter)
{
	one = PlayerOneCounter;
	two = playerTwoCounter;
}

void Board::setBoard(int _height, int _width)
{
	height = _height;
	width = _width;
	board = new Piece**[height];
	board[0] = new Piece*[height*width];
	memset(board[0], 0, height*width * sizeof(*board[0]));
	for (int i = 1; i < height; i++)
		board[i] = board[0] + i * width;
}
;


Piece * Board::getPiece(Point pos)
{
	if (pos.i < 0 || pos.i >= height || pos.j < 0 || pos.j >= width)
		throw "Position " + pos.ToString() + " is out of range";

	return board[pos.i][pos.j];
}

string Board::PlacePiece(Piece * piece, bool seeMe,GameManager* game)
{
	pieces.push_back(piece);
	piece->revealed = seeMe;
	Point pos = piece->GetPosition();
	string res = "ok";

	if (pos.i < 0 || pos.i >= height || pos.j < 0 || pos.j >= width)
		return "Position " + pos.ToString() + " is out of range";
	
	if (board[pos.i][pos.j] != nullptr)
	{
		if (board[pos.i][pos.j]->GetPlayer() == piece->GetPlayer())
		{
			return "Position " + pos.ToString() + " is already occupied by the same player";
		}
		else
		{
			if (board[pos.i][pos.j]->Defend(piece) == Piece::DefendResult::Dead)
			{
				RemovePiece(board[pos.i][pos.j]);
			}
			if (piece->IsAlive())
			{
				
				if (piece->GetPlayer() == Piece::Player::Player1)
				{
					res = one.checkCounter(piece);
				}
				else
				{
					res = two.checkCounter(piece);
				}
				if (res == "ok")
					board[pos.i][pos.j] = piece;
			}
		}
	}
	else
	{
		
		if (piece->GetPlayer() == Piece::Player::Player1)
			res = one.checkCounter(piece);
		else
			res = two.checkCounter(piece);
		if (res == "ok")
					board[pos.i][pos.j] = piece;
	}
	return res;
}

void Board::RemovePiece(Piece * piece)
{
	Point pos = piece->GetPosition();
	if (board[pos.i][pos.j] == piece)
	{
		board[pos.i][pos.j] = nullptr;
	}
}

void Board::PrintWhileWePlay(Point first, Point second,int delay)
{
	Sleep(delay);

	gotoxy(2 + 4 * (first.j), (first.i) * 2 + 1);
	if (board[first.i][first.j] != NULL)
	{
		if (board[first.i][first.j]->GetPlayer() == 0) {
			if (board[first.i][first.j]->IsAlive())
				cout << red << board[first.i][first.j]->ToChar();
			else
				cout << " ";
		}
		else
		{
			if (board[first.i][first.j]->IsAlive())
				cout << yellow << board[first.i][first.j]->ToChar();
			else
				cout << " ";
		}
	}
	else cout << " ";
	gotoxy(2 + 4 * (second.j), (second.i) * 2 + 1);
	if (board[second.i][second.j] != NULL) {
		if (board[second.i][second.j]->GetPlayer() == 0) {
			if (board[second.i][second.j]->IsAlive())
				cout << red << board[second.i][second.j]->ToChar();
			else
				cout << " ";
		}
		else
		{
			if (board[first.i][first.j]->IsAlive())
				cout << yellow << board[first.i][first.j]->ToChar();
			else
				cout << " ";
		}
	}
	else cout << " ";
	gotoxy(1, 22);
	cout << white;
}

void Board::MovePiece(Piece * piece, Point newPos)
{
	Point oldPos = piece->GetPosition();
	board[oldPos.i][oldPos.j] = nullptr;
	piece->revealed = true;
	board[newPos.i][newPos.j] = piece;
}

Board::~Board()
{

	for (Piece * piece : pieces)
		delete piece;
		delete[] board[0];
		delete[] board;
}

string Board::ToString()
{
	stringstream ss;
	for (int i = 0; i < height; i++)
	{
		ss << ' ';
		for (int j = 0; j < width * 4 - 1; j++)
			ss << '-';
		ss << '\n';
		for (int j = 0; j < width; j++)
		{
			ss << "| ";
			if (board[i][j] == nullptr)
				ss << ' ';
			else
				ss << board[i][j]->ToChar();
			ss << ' ';
		}
		ss << "|\n";
	}
	ss << ' ';
	for (int j = 0; j < width * 4 - 1; j++)
		ss << '-';
	ss << '\n';

	return ss.str();

}

void Board::printBoard(bool show1,bool show2,int delay)
{
	/*Sleep(delay);*/

	for (int i = 0; i < height; i++)
	{
		cout << blue << '-';
		for (int j = 0; j < width * 4 - 1; j++)
			cout << blue << '-';
		cout << '\n';
		for (int j = 0; j < width; j++)
		{
			cout << blue << "| ";
			if (board[i][j] == nullptr)
				cout << ' ';
			else
			{
				if (board[i][j]->GetPlayer() == Piece::Player::Player1)
				{
						if (board[i][j]->revealed == false)
							cout << red << "U";
						else
							if (board[i][j]->ToChar() == 'J')
							{
								cout << red << "J" << board[i][j]->ToChar();
							}
							else
								cout << red << board[i][j]->ToChar();
					}
				else
				{
						if (board[i][j]->revealed == false)
							cout << yellow << "U";
						else
							if (board[i][j]->ToChar() == 'J')
							{
								cout << yellow << "J" << board[i][j]->ToChar();
							}
							else
								cout << yellow << board[i][j]->ToChar();
				}
			}
			cout << blue << ' ';
		}
		cout << "|\n";
	}
	cout << '-';
	for (int j = 0; j < width * 4 - 1; j++)
		cout << '-';
	cout << '\n' << white;
}

Board::GAME_STATUS Board::checkStatus(string & reason)
{
	bool playerOneFlag = false, playerTwoFlag = false, playerOneMovable = false, playerTwoMovable = false, playerOneAlive, playerTwoAlive;
	for (Piece * piece : pieces)
	{
		if (piece->IsAlive())
		{
			if (dynamic_cast<Movable *>(piece) != nullptr)
			{
				if (piece->GetPlayer() == Piece::Player::Player1)
					playerOneMovable = true;
				else
					playerTwoMovable = true;
			}
			if (dynamic_cast<Flag *>(piece) != nullptr)
				if (piece->GetPlayer() == Piece::Player::Player1)
					playerOneFlag = true;
				else
					playerTwoFlag = true;
		}

	}
	playerOneAlive = playerOneFlag && playerOneMovable;
	playerTwoAlive = playerTwoFlag && playerTwoMovable;

	if (playerOneAlive && playerTwoAlive)
		return KEEP_PLAYING;
	if (playerOneAlive)
	{
		if (playerTwoFlag)
			reason = "All moving PIECEs of the opponent are eaten";
		else
			reason = "All flags of the opponent are captured";
		return PLAYER_1_WIN;
	}
		
	if (playerTwoAlive)
	{
		if (playerOneFlag)
			reason = "All moving PIECEs of the opponent are eaten";
		else
			reason = "All flags of the opponent are captured";
		return PLAYER_2_WIN;
	}
	reason = "Both players don't have any movable pieces";
	return TIE;
}

list<Joker*> Board::getJokers(Piece::Player player)
{
	list<Joker*> jokers;
	Joker * joker;
	for (Piece * piece : pieces)
	{
		joker = dynamic_cast<Joker *>(piece);
		if (piece->IsAlive() && joker != nullptr && piece->GetPlayer() == player)
		{
			jokers.push_back(joker);
		}
	}
	return jokers;
}
