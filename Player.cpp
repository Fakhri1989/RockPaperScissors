#include "Player.h"

int Playa::player1 = 0;
int Playa::player2 = 0;

Playa::Playa(int who)
{
	Player=who;
	who == 1 ? name = "Player One" : name = "Player Two";
}
