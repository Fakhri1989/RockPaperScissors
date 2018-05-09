#include "Game.h"
#include <iostream>
#include <string.h>
using namespace std;
Game::Game(char ** argv, int argc)
{
	string lookAtMe=argvToString(argv, argc);//copying the argv to string for easier use
	if (isConsole(lookAtMe))
	{
		//PVP game;
	}
	else
	{
		FVF game(lookAtMe);
		game.run(lookAtMe);
	}
}
string Game::argvToString(char ** argv, int argc)
{
	string target;
	if (argc == 1) {
		target = "-delay 50 -show-all";
	}
	else {
		for (int i = 0; i < argc; i++)
		{
			if (i != 0)
				target.append(1, ' ');
			target.append(argv[i]);
		}
	}
	return target;
}

bool Game::isConsole(string target)
{
	string compare = "console";
	bool isConsole = false;
	for (int i = 0; i < target.length(), target[i] != '\0'; i++)
	{
		if (target[i] == 'c')
		{
			isConsole = true;
			while (target[i] != ' ')
				if (target[i] != compare[i])
					isConsole = false;
		}
	}
	return isConsole;
}
