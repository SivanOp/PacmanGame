#pragma once
#include <iostream>
#include "Creature.h"
#include "Ghost.h"

using namespace std;
static int fruitStepCounter;

class Fruit : public Creature
{
public:
	//Constractor:
	Fruit();

	//functions:
	void randomFruitNum() { shape = ((rand() % 5) + 5) + '0'; } //this function returns a random number from {5,6,7,8,9}
	void setFruitPosInBoard(Board& board, Position& pacPos, vector<Ghost>& ghosts, int rows, int cols);
	bool illigalFruitPos(int x, int y, Board& board, Position& pacPos, vector<Ghost>& ghosts, int rows, int cols);
	void setPrevFruit(Position& prevFruit, Board& board, bool colorChoice, Mode currMode);
};



