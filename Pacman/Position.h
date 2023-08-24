#pragma once

#include <conio.h>
#include <windows.h>
#include "board.h"

const int wall = 1;
const int breadCrumbs = 2;
const int emptySpace = 3;
const int ghost = 4;

class Position
{

private:
	int x;
	int y;

public:
	//Constractor:
	Position() { ; }
	Position(int x, int y) { setPosition(x, y); }

	//getters:
	int getPosX() const { return x; }
	int getPosY() const { return y; }

	//setters:
	void setPosition(const int& x, const int& y);

	//Functions:
	void gotoxy();
	int getKey();
	bool check_key(char keyPressed);
	int checkCoord(Board b, int x, int y);

	//operators:
	bool operator==(const Position& pos) const;
	void operator=(const Position& pos);
	bool operator<(const Position& pos) const;
};
