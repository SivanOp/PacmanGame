#include "pacman.h"

//Constractor- set the lives, the score and the starting position of the pacman
Pacman::Pacman() : Creature(Position(40, 10), UP, '@')
{
	lives.amount = 3;
	scoreShown.amount = 0;
}
//Constractor- set the lives, the score and the starting position of the pacman
Pacman::Pacman(int x, int y) : Creature(Position(x,y), UP, '@')
{
	lives.amount = 3;
	scoreShown.amount = 0;
}



