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

	if (piece->GetPlayer() == Piece::Player::Player1)
		res = one.checkCounter(piece);
	else
		res = two.checkCounter(piece);
	if (res != "ok")
		return res;

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
			if (board[pos.i][pos.j]->Defend(piece) == Piece::DefendResult::Dead)//we can do operator overload here
			{
				RemovePiece(board[pos.i][pos.j]);
				if (piece->Defend(board[pos.i][pos.j]) == Piece::DefendResult::Alive)
				{
					board[pos.i][pos.j] = piece;
					board[pos.i][pos.j]->revealed = true;
				}
			}
			else
				board[pos.i][pos.j]->revealed = true;
		}
	}
	else
	{
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

void Board::PrintWhileWePlay(Point first, Point second,int delay,bool knownInfo)
{
	Sleep(delay);

	gotoxy(2 + 4 * (first.j), (first.i) * 2 + 1);
	if (board[first.i][first.j] != NULL)
	{
		if (board[first.i][first.j]->GetPlayer() == 0) {
			PrintHelper(first, knownInfo, red);
		}
		else
		{
			PrintHelper(first,knownInfo,yellow);
		}
	}
	else cout << " ";
	gotoxy(2 + 4 * (second.j), (second.i) * 2 + 1);
	if (board[second.i][second.j] != NULL) {
		if (board[second.i][second.j]->GetPlayer() == 0) {
			PrintHelper(second, knownInfo, red);
		}
		else
		{
			PrintHelper(second, knownInfo, yellow);
		}
	}
	else cout << " ";
	gotoxy(1, 22);
	cout << white;
}

void Board::PrintHelper(Point loc, bool info, color paint)
{
	gotoxy(2 + 4 * (loc.j), (loc.i) * 2 + 1);
	if (board[loc.i][loc.j]->IsAlive())
			cout << paint << board[loc.i][loc.j]->ToChar(info);
	else
		cout << " ";
		
}

void Board::MovePiece(Piece * piece, Point newPos)
{
	Point oldPos = piece->GetPosition();
	board[oldPos.i][oldPos.j] = nullptr;
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
				ss << board[i][j]->pieceInfo();
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

void Board::printBoard(bool show1,bool show2,int delay,bool knownInfo)
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
					
					if (board[i][j]->revealed == false && show2)
						cout << red << board[i][j]->ToChar(knownInfo);
					else
						cout << red << board[i][j]->pieceInfo();
						/*	if (board[i][j]->pieceInfo() == 'J')
							{
								cout << red << "J" << board[i][j]->ToChar();
							}
							else
								cout << red << board[i][j]->ToChar();
*/					}
				else
				{
					if (board[i][j]->revealed == false && show1)
						cout << red << board[i][j]->ToChar(knownInfo);
					else
						cout << red << board[i][j]->pieceInfo();
					/*	if (board[i][j]->revealed == false&&show2)
							cout << yellow << "U";
						else
							if (board[i][j]->ToChar() == 'J')
							{
								cout << yellow << "J" << board[i][j]->ToChar();
							}
							else
								cout << yellow << board[i][j]->ToChar();*/
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

void Board::PrintChanges(bool show1, bool show2,bool knownInfo)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			gotoxy(2 + 4 * j, i * 2 + 1);
			if (board[i][j] == nullptr)
				cout << ' ';
			else if (board[i][j]->GetPlayer()==0)
			{
				if (board[i][j]->revealed == false && show2)
					cout << red << board[i][j]->ToChar(true);
				else
					cout << red << board[i][j]->pieceInfo();
				/*if (board[i][j]->GetPlayer() == Piece::Player::Player1)
				{
					if (board[i][j]->revealed == false && show1)
						cout << red << "U";
					else
						if (board[i][j]->ToChar() == 'J')
						{
							cout << red << "J" << board[i][j]->ToChar();
						}
						else
							cout << red << board[i][j]->ToChar();*/
			}
			else
			{
				if (show1) {
					cout << yellow << board[i][j]->ToChar(true);
				}
				else
					cout << yellow << board[i][j]->pieceInfo();
			}
					/*if (board[i][j]->revealed == false && show)
						cout << yellow << "U";
					else
						if (board[i][j]->ToChar() == 'J')
						{
							cout << yellow << "J" << board[i][j]->ToChar();
						}
						else
							cout << yellow << board[i][j]->ToChar();*/
				
			}
		}
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
