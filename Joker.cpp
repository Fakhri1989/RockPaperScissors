#include "Joker.h"

Piece::DefendResult Joker::Defend(Piece * enemy)
{
	Piece::DefendResult defendResult = myId->Defend(enemy);
	if (!myId->IsAlive())
		this->Die();
	return defendResult;
}

void Joker::Attack(Piece * enemy)
{
	Movable * movable;
	if ((movable = dynamic_cast<Movable *>(myId)) != nullptr)
	{
		movable->Attack(enemy);
		if (movable->IsAlive())
			Move(enemy->GetPosition());
		else
		{
			this->Die();
		}
	}
	else
	{
		throw "I am a bomb, I can't attack!";
	}
}

void Joker::SetID(ID newType)
{
	if (myId != nullptr)
		delete myId;
	switch (newType)
	{
	case Joker::B:
		myId = new Bomb(position, player,gameBoard);
		break;
	default:
		myId = new Soldier(position, player, (Soldier::Type)newType,gameBoard);
		break;
	}
}

char Joker::ToChar()
{
	if (revealed)
		return 'J';
	else
		return tolower(myId->ToChar());
}

string Joker::ToString()
{
	return "Joker";
}
