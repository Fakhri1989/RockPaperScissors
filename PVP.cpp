#include "PVP.h"

int PVP::run()
{
	string data;
	data=TalkToPlayer(START);
	pieceModifier(data, START);
	pieceModifier(data, PLACE);
	pieceModifier(data, MOVE);
	return 0;
}

string PVP::TalkToPlayer(Mode mode)
{
	string data;
	bool proceede = true;
	switch (mode) {
	case START:
		proceede = wannadefaults(SIZE);
		if (proceede) {
			cout << "please Enter Board size in the following format lengthxwidth (no spaces like this=> 10x10)" << endl;
			cin >> data;
			boardSetter(data);
			clearString(data);
		}
		proceede = wannadefaults(NAME);
		if (proceede)
		{
			cout << "Great!!" << endl << "now enter the first player name" << endl;
			cin >> data;
			GameManager::getBoard()->getPlayerOne().setPlayerName(data);
			clearString(data);
			cout << "ok now give me player 2's name " << endl;
			cin >> data;
			data.clear;
		}
		proceede = wannadefaults(NUMBER);
		if (proceede) {
		cout << "oh i forgot how many pieces is each player going to use? (both players must have the same number of pieces in the following format: " << endl << "Flags Bombs Jokers Rocks Papers Scissors (seperating each with a space)" << endl;
		cin >> data.append;
		}

	case PLACE:
		for (int i = 0; i < GameManager::getBoard()->getList().size && proceede == true; i++)
		{
			cout << GameManager::getBoard()->getPlayerOne().getPlayerNAme() + "give me piece type and where to place it" << endl;
			i++;
			cout << GameManager::getBoard()->getPlayerOne().getPlayerNAme() + "give me piece type and where to place it" << endl;

		}
			break;
	case MOVE:
		break;
	default: 
		cout << "Hey BooBoo" << endl;
		break;
	}
	return data;
}

string PVP::pieceModifier(string data, Mode mode)
{
	return string();
}

void PVP::boardSetter(string raw)
{
	int i = 0;
	int length = 0, width = 0;
	string current;
	while (raw[i] != 'x') {
		current.append = raw[i];
		i++;
	}
	i++;
	length = stoi(current);
	current = "";
	for (; i < current.size;i++)
	{
		current.append = raw[i];
	}
	width = stoi(current);
	GameManager::setBoard(length, width);
}

bool PVP::wannadefaults(Comunicate mode)
{
	int res;
	switch (mode) {
	case NAME:
		cout << "do you want default names or your own name?" << endl << "1. default" << endl << "2. my name" << endl;
		cin >> res;
		if (res == 2)
			return true;
		break;
	case SIZE:
		cout << "is a 10x10 board good or do you want something else? " << endl << "1. yes 10x10 is awesome" << endl << "2. no i want different size" << endl;
		cin >> res;
		if (res == 2)
			return true;
		break;
	case NUMBER:
		cout << "ok finally do you want to chose the number of pieces or can i chose for you ?" << endl << "1. I'm lazy you choose" << endl << "2. no ill choose" << endl;
		cin >> res;
		if (res == 2)
			return true;
	}
	return false;
}
