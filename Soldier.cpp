#include "Soldier.h"
#include "Bomb.h"

Piece::DefendResult Soldier::Defend(Piece * enemy)
{
	Soldier * soldier;
	if ((soldier = dynamic_cast<Soldier *>(enemy)) != nullptr)
	{
		if (soldier->type == this->type)
		{
			Die();
			soldier->Die();
			return Piece::DefendResult::Dead;
		}
		else
		{
			bool iWon;
			switch (soldier->type)
			{
			case R:
				iWon = (this->type == P);
				break;
			case P:
				iWon = (this->type == S);
				break;
			case S:
				iWon = (this->type == R);
				break;
			default:
				break;
			}
			if (iWon)
			{
				soldier->Die();
				return Piece::DefendResult::Alive;
				revealed = true;
			}
			else
			{
				this->Die();
				return Piece::DefendResult::Dead;
				enemy->revealed = true;
			}
		}
	}
	if (dynamic_cast<Bomb *>(enemy) != nullptr)
	{
		return Piece::DefendResult::Dead;
	}
	return this->IsAlive() ? Piece::DefendResult::Alive : Piece::DefendResult::Dead;
}

char Soldier::ToChar(bool show)

{
	if (!show)
		return pieceInfo();
	else if (this->revealed)
		return pieceInfo();
	else
		return 'U';
	}

char Soldier::pieceInfo()
{
	switch (this->type)
	{
	case R:
		return 'R';
		break;
	case P:
		return 'P';
		break;
	case S:
		return 'S';
		break;
	default:
		throw "Bad soldier type";
		break;
	}
}


string Soldier::ToString()
{
	switch (this->type)
	{
	case R:
		return "Rock";
		break;
	case P:
		return "Paper";
		break;
	case S:
		return "Scissors";
		break;
	default:
		throw "Bad soldier type";
		break;
	}
}

