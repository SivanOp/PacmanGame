#include "Fruit.h"

Fruit::Fruit() : Creature(Position(40, 12), UP, '5')
{

}

//this function selects randomly a position for the fruit on the board
void Fruit::setFruitPosInBoard(Board& board, Position& pacPos,vector<Ghost>& ghosts, int rows, int cols)
{
	int x, y;
	x = rand() % rows;
	y = rand() % cols;

	while (illigalFruitPos(x, y, board, pacPos, ghosts, rows, cols)) //if the position is illigal
	{
		x = rand() % rows;
		y = rand() % cols;
	}

	setPos(Position(y,x));
}

//this function checks if the position of the fruit is illigal
bool Fruit::illigalFruitPos(int x, int y, Board& board, Position& pacPos, vector<Ghost>& ghosts, int rows, int cols)
{

	for (int i = 0; i < ghosts.size(); i++) //the fruit cant be in the ghosts position
	{
		if (creaturePos == ghosts[i].getPos())
			return true;
	}
	if (board.getCoord(y, x) == '#' || x == 0 || x >= cols || y == 0 || y >= rows) //the fruit cant be in a wall position, or outside the board limits
		return true;
	else
		return false;
}

//this function sets the prev position of the fruit
//then, it prints on the board the prev char of this position
void Fruit::setPrevFruit(Position& prevFruit, Board& board, bool colorChoice, Mode currMode)
{
	prevFruit.setPosition(creaturePos.getPosX(), creaturePos.getPosY());
	if ((int)currMode != 3) //except silent mode- no printing to screen needed
	{
		if (colorChoice)
			textcolor(04);
		else
			textcolor(07);

		prevFruit.gotoxy();
		cout << board.getCoord(prevFruit.getPosX(), (prevFruit.getPosY())) << endl;
	}

}

