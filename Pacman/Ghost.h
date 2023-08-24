#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "pacman.h"
#include "Creature.h"
#include "General.h"
#include <queue>
#include <map>
#include <set>


class Ghost : public Creature
{

private:
	Position prevPos;
	int movesCounter;

public:
	//Constractor:
	Ghost(int x, int y);

	//getters:
	Position& getPrevPos() { return prevPos; }

	//setters:
	void setPrevPos(const Position& otherPos) { prevPos = otherPos; }

	//Functions:
	void setPrevGhost(vector<Ghost>& ghosts, Board& board, Position& pacPos, bool colorChoice, Mode currMode);
	void moveGhost(Board& board, char levelChoice, Pacman& pac, int rows, int cols);
	void bfsMove(Pacman& pac,Board& board, int rows, int cols);
};
