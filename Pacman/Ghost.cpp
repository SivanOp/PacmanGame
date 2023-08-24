#include "Ghost.h"

using namespace std;

Ghost::Ghost(int x, int y) : Creature(Position(x, y), (Direction)UP, '$')
{
	movesCounter = 0;
}

//this function sets the prev position of the ghosts 
//then, it prints on the board the prev char of this position
void Ghost::setPrevGhost(vector<Ghost>& ghosts,Board& board, Position& pacPos, bool colorChoice, Mode currMode)
{
	int i;

	for (i = 0; i < ghosts.size(); i++)
	{
		ghosts[i].setPrevPos(ghosts[i].getPos());
	}
	if ((int)currMode != 3)
	{
		if (colorChoice)
			textcolor(04);
		else
			textcolor(07);

		for (i = 0; i < ghosts.size(); i++)
		{
			ghosts[i].getPrevPos().gotoxy();
			cout << board.getCoord(ghosts[i].getPrevPos().getPosX(), ghosts[i].getPrevPos().getPosY());
		}
	}
}

//this function moves the ghosts acoording to the levels choice 
void Ghost::moveGhost(Board& board, char levelChoice, Pacman& pac, int rows,int cols)
{
	bool res;
	if (levelChoice == 'a')//BEST
	{ //the smart ghosts tries to chase the pacman using bfs algorithym
		bfsMove(pac, board, rows, cols); 
		res = moveCreatureByDir(dir, board, rows,cols);

		while (res == false)//if the new direction is not valid it will continue to pick the next direction 
		{
			dir = (Direction)randomDir();
			res = moveCreatureByDir(dir, board, rows, cols);
		}
	}
	else if (levelChoice == 'b')//GOOD
	{ //every 20 moves, the smart ghosts will turn to novice ghosts for 5 steps
		if (movesCounter >= 20 && movesCounter < 25)
		{
			Creature::moveCreature(board, rows, cols);
			if (movesCounter == 24)
				movesCounter = 0;
		}
		else
		{
			bfsMove(pac, board, rows, cols);
			res = moveCreatureByDir(dir, board, rows, cols);

			while (res == false)//if the new direction is not valid it will continue to pick the next direction 
			{
				dir = (Direction)randomDir();
				res = moveCreatureByDir(dir, board, rows, cols);
			}
		}
	}
	else//NOVICE
		//this function changes the creature direction every 5 moves by calling the function randomDir
		Creature::moveCreature(board, rows, cols); 

	movesCounter++;
}

// BFS algorithym 
void Ghost::bfsMove(Pacman& pac, Board& board, int rows, int cols)
{
	set<Position>visited; // set for all the positions the ghost already visited in
	queue<Position>Q; // saves a current path 
	Q.push(creaturePos);
	Position position;
	map<Position, Position> prev; // saves all the possible positions
	map<Position, Direction> prev_dir;// saves all the possible directions acoording to the positions in map prev
	int iterations = 0;

	while (!Q.empty())
	{
		position = Q.front();
		Q.pop();

		if (pac.getPos() == position) //if we found a path leading to the pacman
			break;

		visited.insert(position);
		
		//4 directions- 0- UP, 1- DOWN, 2- LEFT, 3- RIGHT
		for (int dir = 0; dir < 4; ++dir)
		{
			Position next_position = Creature::getCreatureNewPositionByDir(position, (Direction)dir);

			//check if the current position is lligal- if the position is in the board limits
			if (next_position.getPosX() >= 0 && next_position.getPosX() < cols && next_position.getPosY() >= 0 && next_position.getPosY() < rows)
			{
				//if the board in this position is not wall and not been visited already
				if ((board.getCoord(next_position.getPosX(), next_position.getPosY()) != '#') && (visited.find(next_position) == visited.end()))
				{
					prev[next_position] = position; //save the position in map
					prev_dir[next_position] = (Direction)dir; //save the direction in map
					Q.push(next_position);
				}
			}
			iterations++;
			if (iterations >= 10000) 
				break;
		}
	}
	Position pos = pac.getPos();

	//runs on all the path positions in order to find the first step 
	while (prev.find(pos) != prev.end() && !(prev[pos] == creaturePos))
	{
		pos = prev[pos];
	}

	//if a path not found, select a random direction
	if (prev.find(pos) == prev.end())
	{
		dir = (Direction)randomDir();
	}
	else
	{
		dir = prev_dir[pos];
	}
}


