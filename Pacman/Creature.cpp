#include "Creature.h"


Creature::Creature(Position creaturePos, Direction dir, char shape)
{
	setPos(creaturePos);
	setDir(dir);
	setShape(shape);
}

void Creature::printCreature(bool colorChoice)
{
	creaturePos.gotoxy();
	if (colorChoice)
		textcolor(06);
	else
		textcolor(07);

	cout << shape << endl;

	if (colorChoice)
		textcolor(04);
	else
		textcolor(07);
}

//this function returns a random number from {0,1,2,3}
int Creature::randomDir()
{
	int dir;
	dir = rand() % 4;
	return dir;
}

//this function changes the creature direction every 5 moves by calling the function randomDir
void Creature::moveCreature(Board& board, int rows, int cols)
{
	bool res;
	if (stepCounter == 0)
	{
		dir = (Direction)randomDir();
		stepCounter = 20;
	}
	else
		stepCounter--;

	res = moveCreatureByDir(dir, board, rows, cols);

	while (res == false)//if the random direction is not valid it will continue to pick the next direction  
	{
		dir = (Direction)randomDir();
		res = moveCreatureByDir(dir, board, rows,cols);
	}

}

//this function returns the position of the creature + one step in direction dir
Position Creature::getCreatureNewPositionByDir(Position position, Direction dir)
{
	int newX = 0, newY = 0;
	switch (dir)
	{
	case 0://Up
		newX = position.getPosX();
		newY = position.getPosY() - 1;
		break;
	case 1://Down
		newX = position.getPosX();
		newY = position.getPosY() + 1;
		break;
	case 2://Left
		newX = position.getPosX() - 1;
		newY = position.getPosY();
		break;
	case 3://Right
		newX = position.getPosX() + 1;
		newY = position.getPosY();
		break;
	case 4:
		newX = position.getPosX();
		newY = position.getPosY();
		break;
	}
	return Position(newX, newY);
}

//this function moves the creature on the board according to the direction that was picked
bool Creature::moveCreatureByDir(Direction dir, Board& board, int rows, int cols)
{
	Position newPosition = getCreatureNewPositionByDir(creaturePos, dir);

	int newX = newPosition.getPosX();
	int newY = newPosition.getPosY();
	bool res = true;

	if (board.getCoord(newX, newY) == '#')//direction is inValid
		res = false;

	else if (newX >= cols || newX <= 0 || newY >= rows || newY <= 0) //check that the coord is inside the board limits
		res = false;
	else
		creaturePos.setPosition(newX, newY);
	return res;
}