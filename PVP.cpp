#pragma once
#include "PVP.h"
#include "Piece.h"

void PVP::run(){

	int height, width;
	int rocks, papers, scissors, jokers, bombs, flags;
	string PieceType, jokerType, input, error, reason;
	int x0, y0,x1,y1,jx,jy;
	char c;
	Joker * joker;
	int turn = 1;
	bool playerOneDonePlacement = false;
	bool playerTwoDonePlacement = false;
	bool isPlayerOneCurrentlyPlaying = true;

	cout << "********************************************************\nLet's start the game!!\n\n what is the height of the board? ";
	cin >> height;
	cout << "OK, and the width? ";
	cin >> width;
	cout << "How many rocks each player has? ";
	cin >> rocks;
	cout << "How many papers each player has? ";
	cin >> papers;
	cout << "How many scissors each player has? ";
	cin >> scissors;
	cout << "How many Jokers each player has? ";
	cin >> jokers;
	cout << "How many bombs each player has? ";
	cin >> bombs;
	cout << "How many flags each player has? ";
	cin >> flags;

	Counter PlayerOneCounter(rocks, papers, scissors, jokers, bombs, flags);
	Counter PlayerTwoCounter(rocks, papers, scissors, jokers, bombs, flags);
	setBoard(height, width);
	gameBoard.setCounters(PlayerOneCounter, PlayerTwoCounter);
	bool badInput = false;
	while (!playerOneDonePlacement || !playerTwoDonePlacement)
	{
		do
		{
			if (turn != 1)
			{
				gameBoard.PrintChanges(isPlayerOneCurrentlyPlaying, !isPlayerOneCurrentlyPlaying,true);
				cout << white;
				gotoxy(0, gameBoard.getHeight() * 2 + 1);
				cout << "                                                                                                                " << endl;
				cout << "                                                                                                                " << endl;
				cout << "                                                                                                                " << endl;
				cout << "                                                                                                                " << endl;
				cout << "                                                                                                                " << endl;
				cout << "                                                                                                                " << endl;
				cout << "                                                                                                                " << endl;
				gotoxy(0, gameBoard.getHeight() * 2 + 1);
			}
			badInput = false;
			cout << "\nPlayer " << (isPlayerOneCurrentlyPlaying ? "one" : "two") << ": What piece type would you like to place now? {R = rock, P = paper, S = scissors, J = joker, B = bomb, F = flag, X = end placement}: ";
			cin >> PieceType;


			if (PieceType == "X")
			{
				if (isPlayerOneCurrentlyPlaying)
					playerOneDonePlacement = true;
				else
					playerTwoDonePlacement = true;
			}
			else
			{
				cout << "And where (x,y) on the board to place it? ";
				cin >> x0 >> y0;
				if (PieceType == "J")
				{
					cout << "What is the initial representation of this joker?";
					cin >> jokerType;
					input = PieceType + " " + to_string(x0) + " " + to_string(y0) + " " + jokerType;
				}
				else
					input = PieceType + " " + to_string(x0) + " " + to_string(y0);
				error = parsePlacement(input, isPlayerOneCurrentlyPlaying ? Piece::Player::Player1 : Piece::Player::Player2);
				if (error != "ok")
				{
					cout << "\nThe following has occured: \n  " << error << endl;
					badInput = true;
				}
			}
		} while (badInput);
		if (!playerOneDonePlacement)
			playerOneDonePlacement = gameBoard.GetPlayerOneCounter().isFull();
		if (!playerTwoDonePlacement)
			playerTwoDonePlacement = gameBoard.GetPlayerTwoCounter().isFull();
		if (isPlayerOneCurrentlyPlaying && !playerTwoDonePlacement)
			isPlayerOneCurrentlyPlaying = false;
		else if(!isPlayerOneCurrentlyPlaying && !playerOneDonePlacement)
			isPlayerOneCurrentlyPlaying = true;
		if (turn == 1)
		{
			system("CLS");
			gameBoard.printBoard(isPlayerOneCurrentlyPlaying, !isPlayerOneCurrentlyPlaying, 0,true);
			turn++;
		}
			//gameBoard.PrintChanges(isPlayerOneCurrentlyPlaying, !isPlayerOneCurrentlyPlaying,true);

	}

	cout << "********************************************************\nfinished placement of both players\n********************************************************\n   start playing the game\n******************************************************** ";
	badInput = false;

	Board::GAME_STATUS status;

	while((status = gameBoard.checkStatus(reason)) == Board::GAME_STATUS::KEEP_PLAYING)
	{

		do {
			badInput = false;
			cout << "\nPlayer " << (isPlayerOneCurrentlyPlaying ? "one" : "two") << ": Choose a point from where you want to move your piece: ";
			cin >> x0 >> y0;
			cout << "And where would you move it to? ";
			cin >> x1 >> y1;
			error = parseMove(x0, y0, x1, y1, isPlayerOneCurrentlyPlaying ? Piece::Player::Player1 : Piece::Player::Player2);
			if (error != "ok")
			{
				cout << "\nThe following has occured: \n  " << error << endl;
				badInput = true;
			}
		} while (badInput);

		do {
			badInput = false;
			list <Joker *> jokers = gameBoard.getJokers(isPlayerOneCurrentlyPlaying ? Piece::Player::Player1 : Piece::Player::Player2);
			if (jokers.size() > 0)
			{
				cout << "Want to change a represantation for a joker (Y/N)? ";
				cin >> c;
				if (c == 'Y')
				{
					if (jokers.size() == 1)
					{
						jx = jokers.front()->GetPosition().j;
						jy = jokers.front()->GetPosition().i;
					}
					else
					{
						cout << "where is the joker located(x,y)? ";
						cin >> jx >> jy;
					}

					cout << "change to what?";
					cin >> c;
					error = parseJoker(jx, jy, c, isPlayerOneCurrentlyPlaying ? Piece::Player::Player1 : Piece::Player::Player2);

				}
				else if (c != 'N')
					badInput = true;

			}


			if (error != "ok")
			{
				cout << "\nThe following has occured: \n  " << error << endl;
				badInput = true;
			}
		} while (badInput);

		isPlayerOneCurrentlyPlaying = !isPlayerOneCurrentlyPlaying;
	}

	switch (status)
	{
	case Board::TIE:
		cout << "The game ended in a tie. \n reason: " << reason << endl;
		break;
	case Board::PLAYER_1_WIN:
		cout << "The game ended, player one - YOU WIN!!!!. \n reason: " << reason << endl;
		break;
	case Board::PLAYER_2_WIN:
		cout << "The game ended, player two - YOU WIN!!!!. \n reason: " << reason << endl;
		break;
	default:
		break;
	}


}

string PVP::parseMove(int x0, int y0, int x1, int y1, Piece::Player player)
{
	Movable * movable;
	Piece * piece, *enemy;
	int status, jx, jy;
	char c;

	status = checkIfDistanceOk(x0, y0, x1, y1);


	if (!status)
	{
		return "moving this distance or this direction just cant be done buddy!!";
	}

	else
	{
		Point pos1(x0, y0);

		if ((piece = (*getBoard())[pos1]) != nullptr)
		{
			if (piece->GetPlayer() == player)
			{
				if ((movable = dynamic_cast<Movable *>(piece)) != nullptr)
				{
					Point enemyPos(x1, y1);
					enemy = (*getBoard())[enemyPos];

					if (enemy == nullptr)
					{
						getBoard()->MovePiece(piece, enemyPos);
					}
					else
					{
						if (piece->GetPlayer() != enemy->GetPlayer())
						{
							movable->Attack(enemy);
							Kill(movable, enemy);
						}
						else
							return "you can NOT attack your own pieces";
					}

				}
				else
					return "tried to move a stationary piece";
			}
			else
				return "Player tried to move the opponents piece";
		}
		else
			return "Vacant point, no piece to move";

		return "ok";
	}
}
string PVP::parseJoker(int jx, int jy, char c, Piece::Player player)
{
	Joker * joker;
	Point pos(jx, jy);
	Piece * piece = (*getBoard())[pos];
	if (piece != nullptr)
	{
		if (piece->GetPlayer() == player)
		{
			if ((joker = dynamic_cast<Joker *>(piece)) != nullptr)
			{
				switch (c)
				{
				case 'R':
					joker->SetID(Joker::ID::R);
					return "ok";
					break;
				case 'P':
					joker->SetID(Joker::ID::P);
					return "ok";
					break;
				case 'S':
					joker->SetID(Joker::ID::S);
					return "ok";
					break;
				case 'B':
					joker->SetID(Joker::ID::B);
					return "ok";
					break;
				default:
					return "Bad input- wrong type for Joker";
					break;
				}
			}
			else
				return "The position " + pos.ToString() + " does not occupy a Joker";
		}
		else
			return "Player tried to change the opponents joker!! WTF????";
	}
	else
		return "The position " + pos.ToString() + " is empty";

	return "ok";
}
