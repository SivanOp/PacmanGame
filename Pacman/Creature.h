#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <typeinfo>
#include "Position.h"
#include "Color.h"
#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT, STAY };
static int stepCounter;


using namespace std;

class Creature
{
protected:
	Position creaturePos;
	Position initialPos;
	Direction dir;
	char shape;

public:

	//Constractor:
	Creature();
	Creature(Position creaturePos, Direction dir, char shape);

	//getters:
	Position& getPos() { return creaturePos; }
	Position& getInitialPos() { return initialPos; }
	Direction getDir() { return dir; }
	char getShape() const { return shape; }

	//setters:
	void setPos(const Position& otherPos) { creaturePos = otherPos; }
	void setInitialPos(const Position& otherPos) { initialPos = otherPos; }
	void setDir(const Direction& otherDir) { dir = otherDir; }
	void setShape(const char& otherShape) { shape = otherShape; }

	//Functions:
	void printCreature(bool colorChoice);
	int randomDir();
	void moveCreature(Board& board, int rows, int cols);
	bool moveCreatureByDir(Direction dir, Board& board, int rows, int cols);
	Position getCreatureNewPositionByDir(Position position, Direction dir);
};
