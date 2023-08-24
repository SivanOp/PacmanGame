#include "Position.h"
using namespace std;

void Position::gotoxy()
{
	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { x,y };
	cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

int Position::getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}

bool Position::check_key(char keyPressed)
{
	switch (keyPressed)
	{
	case 'A':
	case 'a':
	case 'D':
	case 'd':
	case 'W':
	case 'w':
	case 'X':
	case 'x':
	case 'S':
	case 's':
		return true;
	default:
		return false;
	}
}

int Position::checkCoord(Board b, int x, int y)
{
	if (b.getCoord(x, y) == '#')
		return wall;
	if (b.getCoord(x, y) == '.')
		return breadCrumbs;
	if (b.getCoord(x, y) == ' ' || b.getCoord(x, y) == '%')
		return emptySpace;
}

void Position::setPosition(const int& x, const int& y)
{
	this->x = x;
	this->y = y;
}

// compares between two positions- checks if X values are equal and Y values are equal
bool Position::operator==(const Position& pos) const
{
	if (x == pos.getPosX() && y == pos.getPosY())
		return true;
	else
		return false;
}

// sets the position to the new position
void Position::operator=(const Position& pos)
{
	x = pos.getPosX();
	y = pos.getPosY();
}

// compares between two positions - checks if the given position is bigger
bool Position::operator<(const Position& pos) const
{
	if (x < pos.getPosX() || (x == pos.getPosX() && y < pos.getPosY()))
		return true;
	return false;

}
