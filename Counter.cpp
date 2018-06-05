#include "Counter.h"
#include "Bomb.h"
#include "Flag.h"
#include "Joker.h"
#include "Piece.h"
#include "Soldier.h"
using namespace std;

string Counter::checkCounter(Piece * piece)
{

	if (dynamic_cast<Flag *>(piece) != nullptr)
	{
		flag++;
		if (flag > maxFlags)
			return "Player tried to put *" + to_string(flag) + "* flags!";
	}
	if (dynamic_cast<Bomb *>(piece) != nullptr)
	{
		bomb++;
		if (bomb > maxBombs)
			return "Player tried to put *" + to_string(bomb) + "* bombs!";
	}
	if (dynamic_cast<Joker *>(piece) != nullptr)
	{
		joker++;
		if (joker > maxJokers)
			return "Player tried to put *" + to_string(joker) + "* jokers";
	}
	Soldier * soldier;
	if ((soldier = dynamic_cast<Soldier *>(piece)) != nullptr)
	{
		switch (soldier->type)
		{
		case Soldier::R:
			rock++;
			if (rock > maxRocks)
				return "Player tried to put *" + to_string(rock) + "* rocks";
			break;
		case Soldier::S:
			scissors++;
			if (scissors > maxScissors)
				return "Player tried to put *" + to_string(scissors) + "* scissors";
			break;
		case Soldier::P:
			paper++;
			if (paper > MaxPapers)
				return "Player tried to put *" + to_string(paper) + "* papers";
			break;
		default:
			return "This type of piece does NOT exist in our game";
			break;
		}
	}
	return "ok";
}
