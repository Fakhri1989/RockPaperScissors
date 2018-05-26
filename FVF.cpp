#include "FVF.h"

FVF::FVF(string _parameters) :parameters(_parameters)
{
	setBoard(10, 10);
}
int FVF::run(string gameOn)
{
	int winner;
	string reason;
	LineError out;
	//int seeMe=1;
	int playerOneLineFailure = 0, playerTwoLineFailure = 0;
	bool startGame = updateParameters(gameOn);
	if (!startGame)
	{
		cout << "Invalid parameters entered" << endl;
		return 0;
	}
	out = parsePlacementFile("player1.rps_board", Piece::Player::Player1);
	if (out.fileName != REG)
	{
		playerOneLineFailure = out.lineNumber;
		winner = 2;
		reason = "Bad Positioning input file for player 1 - line " + to_string(playerOneLineFailure) + ":\n     " + out.reason;
		cout << out.ToString() << endl;
	}

	out = parsePlacementFile("player2.rps_board", Piece::Player::Player2);
	if (!quiet)
		getBoard()->printBoard(show1, show2, delayTime);
	if (out.fileName != REG)
	{
		playerTwoLineFailure = out.lineNumber;
		winner = 1;
		reason = "Bad Positioning input file for player 2 - line " + to_string(playerTwoLineFailure) + ":\n     " + out.reason;
		cout << out.ToString() << endl;
	}

	if (playerOneLineFailure > 0 && playerTwoLineFailure > 0)
	{
		ofstream out;
		winner = 0;
		reason = "Bad Positioning input file for both players - player 1: line " + to_string(playerOneLineFailure) + ", player 2: line " + to_string(playerTwoLineFailure);
		out.open("rps.output");
		out << "Winner: " + to_string(winner) + "\n";
		out << "Reason: " + reason + "\n\n";
		out << getBoard()->ToString() + "\n";
		out.close();
	}
	else if (playerOneLineFailure > 0)
	{
		ofstream out;
		out.open("rps.output");
		out << "Winner: " + to_string(winner) + "\n";
		out << "Reason: " + reason + "\n\n";
		out << getBoard()->ToString() + "\n";
		out.close();
	}
	else if (playerTwoLineFailure > 0)
	{
		ofstream out;
		out.open("rps.output");
		out << "Winner: " + to_string(winner) + "\n";
		out << "Reason: " + reason + "\n\n";
		out << getBoard()->ToString() + "\n";
		out.close();
	}
	else
	{
		//	if(!quiet)
		//	//board.printBoard(show1,show2);

		out = parseMoveFile("player1.rps_moves", "player2.rps_moves", winner, reason);

		if (out.fileName != REG)
		{
			winner = out.player == Piece::Player::Player1 ? 2 : 1;
			reason = "Bad Moves input file for player " + (out.player == Piece::Player::Player1 ? to_string(1) : to_string(2)) + " - line " + to_string(out.lineNumber);
			cout << out.ToString() << endl;
		}

		ofstream out;
		out.open("rps.output");
		out << "Winner: " + to_string(winner) + "\n";
		out << "Reason: " + reason + "\n\n";
		out << getBoard()->ToString() + "\n";
		out.close();
	}
	return 0;
}

int FVF::getInfoFromLine(string str, int & x, int & y, int & nx, int & ny, int & jx, int & jy, char & jt)
{
	bool check;
	int index = 0;
	x = y = nx = ny = 0;
	jx = jy = -1;
	check = catchFirstNum(str, x, index);

	if (index == str.length() || !check)return 0;//BAD FORMAT

	check = catchFirstNum(str, y, index);

	if (index == str.length() || !check)return 0;
	check = catchFirstNum(str, nx, index);

	if (index == str.length() || !check)return 0;
	check = catchFirstNum(str, ny, index);

	//if (index == str.length() && check)return 1;
	if (check)
	{
		if (str.length() - index > 0)
		{
			if (str[index] == 'J'&&str[index + 1] == ':'&&str[index + 2] == ' ')
			{
				index = index + 3;

				check = catchFirstNum(str, jx, index);
				if (index == str.length() || !check)return 0;
				check = catchFirstNum(str, jy, index);
				if (index == str.length() || !check)return 0;
				if (str[index] == 'R' || str[index] == 'P' || str[index] == 'S' || str[index] == 'B')
				{
					jt = str[index++];
				}
			}
			else while (str[index] == ' '&&index<str.length())index++;
			if (index == str.length())return 1;
			else 0;
		}
		else while (str[index] == ' '&&index<str.length())index++;
		if (index == str.length() || str[index] == '/n')return 1;
		else 0;
	}

	return 0;
}

bool FVF::updateParameters(string update)
{
	string target, delayThingy;
	//char c;
	int i = 0;
	bool isItOk;
	for (i; i < update.length(); i++)
	{
		delayThingy = "";
		target = "";
		while (i < update.length() && update[i] != ' ')
		{
			target.append(1, update[i]);
			if (target == "-delay")
			{
				i += 2;
				while (update[i] != ' ')
				{
					delayThingy.append(1, update[i]);
					i++;
				}
				i--;
				isItOk = changeDelay(stoi(delayThingy));
			}
			else
			{
				if (target == "-show")
				{
					i++;
					target.append(1, update[i]);
					i++;
					while (i <= update.length() && update[i] != ' ')
					{
						target.append(1, update[i]);
						i++;
					}
					isItOk = changeTheOthers(target);
				}

			}
			i++;
		}
		if (!isItOk)
		{
			return false;
		}
		if (quiet == true)
			delay = 0;
	}
	if (!show1 && !show2 && !quiet)
	{
		show1 = true;
		show2 = true;
	}
	return true;
}

bool FVF::changeTheOthers(string parameter)
{

		string showAll = "-show-all";
		showAll.append(1, '\0');
		if (parameter == "-show 1")
		{
			if (show1 == false)
			{
				show1 = true;
				return true;
			}
			else return false;
		}
		else if (parameter == "-show 2")
		{
			{
				if (show2 == false)
				{
					show2 = true;
					return true;
				}
			}
		}
		else if (parameter == showAll)
		{
			{
				if (show1 == false)
					show1 = true;
				else return false;
				if (show2 == false)
					show2 = true;
				else return false;
			}
			return true;
		}
		else if (parameter == "-show-only-known-info")
		{
			if (onlyKnownInfo == false)
			{
				onlyKnownInfo = true;
				return true;
			}
		}
		else if (parameter == "-quiet")
		{
			if (quiet == false)
			{
				quiet = true;
				return true;
			}
		}
		return false;//we have made it so if you try to update the same field twice it will be an error

}

bool FVF::changeDelay(int time)
{
	if (delay == false)
	{
		delay = true;
		delayTime = time;
		return true;
	}
	return false;
}

bool FVF::catchFirstNum(string str, int & x, int & index)
{
	int help;
	x = 0;
	bool check = 0;
	while (str[index] != ' '&&index<str.length())
	{
		help = (str[index++] - '0');
		x = help + x * 10;
		if (help < 0) return 0;
		check = 1;
	}

	if (index < str.length())
		index++;
	else
		return check;
	if (index == str.length())
		return 0;
	else
		return check;
}

LineError FVF::parsePlacementFile(string path, Piece::Player player)
{
	int lineNum = 0;
	string input;
	string result;
	LineError out;
	fstream in;
	in.open(path);
	if (!in.is_open())
		return LineError(path, lineNum, player, "File was not found");

	while (!in.eof())
	{
		getline(in, input);
		lineNum++;

		result = parsePlacement(input, player);
		if (result != "ok")
		{
			return LineError(path, lineNum, player, result);
		}
	}
	in.close();
	return out;
}

LineError FVF::parseMoveFile(string player1File, string player2File, int & winner, string & reason)
{
	bool endGame = false;
	bool player1Turn = true;
	string line;
	fstream f1, f2;
	int counter1, counter2;
	LineError ok;
	f1.open(player1File);
	f2.open(player2File);
	counter1 = counter2 = 0;
	if (!f1.is_open())
		return LineError(player1File, 0, Piece::Player::Player1, "File was not found");
	if (!f2.is_open())
		return LineError(player2File, 0, Piece::Player::Player2, "File was not found");
	while ((!f1.eof() || !f2.eof()) && !endGame)
	{
		if (player1Turn)
		{
			if (f1.eof())
			{
				getline(f2, line);
				player1Turn = false;
			}
			else
			{
				getline(f1, line);
			}
		}
		else
		{
			if (f2.eof())
			{
				getline(f1, line);
				player1Turn = true;
			}
			else
			{
				getline(f2, line);
			}
		}
		int now = (player1Turn ? ++counter1 : ++counter2);
		string path = (player1Turn ? player1File : player2File);

		string exeption = parseMove(line, player1Turn ? Piece::Player::Player1 : Piece::Player::Player2);


		if (exeption != "ok") {
			if (player1Turn)
				return LineError(player1File, now, Piece::Player::Player1, exeption);
			else
				return LineError(player2File, now, Piece::Player::Player2, exeption);
		}


		Board::GAME_STATUS status = getBoard()->checkStatus(reason);

		if (status != Board::KEEP_PLAYING)
			endGame = true;

		switch (status)
		{
		case Board::TIE:
			winner = 0;
			break;
		case Board::PLAYER_1_WIN:
			winner = 1;
			break;
		case Board::PLAYER_2_WIN:
			winner = 2;
			break;
		}
		player1Turn = !player1Turn;
	}

	f1.close();
	f2.close();
	if (!endGame)
	{
		winner = 0;
		reason = "A tie - both Moves input files done without a winner";
	}
	return ok;
}

string FVF::parseMove(string input, Piece::Player player)
{
	Movable * movable;
	Piece * piece, *enemy;
	int x0, y0, x1, y1, jx, jy, status;
	char c;

	status = getInfoFromLine(input.c_str(), x0, y0, x1, y1, jx, jy, c);
	if (status)
	{
		status = checkIfDistanceOk(x0, y0, x1, y1);
		if (!status)
		{
			return"moving this distance or this direction just cant be done buddy!!";
		}
	}
	if (status == 1)
	{
		Point pos1(x0, y0);

		if ((piece = getBoard()->getPiece(pos1)) != nullptr)
		{
			if (piece->GetPlayer() == player)
			{
				if ((movable = dynamic_cast<Movable *>(piece)) != nullptr)
				{
					Point enemyPos(x1, y1);
					enemy = getBoard()->getPiece(enemyPos);

					if (enemy == nullptr)
					{
						getBoard()->MovePiece(piece, enemyPos);
						if (!quiet)
							getBoard()->PrintWhileWePlay(pos1, enemyPos, delayTime);
					}
					else
					{
						if (piece->GetPlayer() != enemy->GetPlayer())
						{
							movable->Attack(enemy);
							Kill(movable, enemy);
							if (!quiet)
								getBoard()->PrintWhileWePlay(pos1, enemyPos, delayTime);
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

		if (jx != -1 && jy != -1)
		{
			Joker * joker;
			Point pos(jx, jy);
			Piece * piece = getBoard()->getPiece(pos);
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
						if (!quiet)
							getBoard()->PrintWhileWePlay(pos, pos, delayTime);
					}
					else
						return "The position " + pos.ToString() + " does not occupy a Joker";
				}
				else
					return "Player tried to move the opponents piece";
			}
			else
				return "The position " + pos.ToString() + " is empty";
		}
	}
	else 	return "input does not meet criteria. only <FROM_X> <FROM_Y> <TO_X> <TO_Y> [J: <Joker_X> <Joker_Y> <NEW_REP>] is allowed.";
	return "ok";
}
