#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "pacman.h"
#include "board.h"
#include "Position.h"
#include "Game.h"
#include "Ghost.h"
#include "Color.h"
#include "Fruit.h"
#include "vector"
#include "General.h"

using namespace std;

class Game
{
public:
	//Functions:
	void startGame(Pacman& pacman, char levelChoice, Board& board, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode, int& currScreen);
	void printInstructions(bool colorChoice, Board& board, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode);
	int printMenu(bool colorChoice, Board& board, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode);
	void gameLoop(char keyPressed,Pacman& pacman, Board& board, vector<Ghost>& ghosts, bool colorChoice, char levelChoice, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode, int& currScreen);
	void updateCoordByKey(char keyPressed, Pacman& pacman, int x, int y);
	void tunnelMove(Position& pacPos, Position& pacPrevPos, Pacman& pacman, Board& board, int& breadcrumbsEaten, Mode currMode);
	bool checkWin(Board& board, int breadcrumbsEaten, Mode currMode);
	bool checkColisionPG(Position& pacPos, vector<Ghost>& ghosts);
	bool checkColisionGF(Position& fruitPos, vector<Ghost>& ghosts);
	bool checkColisionPF(Fruit& fruit, Position& fruitPos, Pacman& pacman, Board& board);
	bool checkLose(Pacman& pacman, Mode currMode);
	void gameLoopLoad(Pacman& pacman, char colorChoice, Board& board, vector<Ghost>& ghosts, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode, int& currScreen);
	void Tunnels(Pacman& pacman, vector<Position>& tunnelsPos, Position& pacPrevPos, Board& board, int rows, int cols,int& breadcrumbsEaten, Mode currMode);
	void pacInLoad(Position& pacPrevPos, Pacman& pacman, char* dup, string line, int& breadcrumbsEaten, Board& board, int& dir, vector<Position>& tunnelsPos, int rows, int cols, Mode currMode);
	void ghostInLoad(char* dup, string line, int& dir, int& ghostNum, Board& board, int rows, int cols, vector<Ghost>& ghosts, Mode currMode);
	void fruitInLoad(Fruit& fruit, Position& prevFruit, Board& board, bool colorChoice, int rows, int cols, string line, char* dup, bool newFruit, int& dir, Mode currMode);
	bool checkIfGoodResult(vector<int>result, string fileName, Pacman& pacman, Board& board, int breadCrumbsEaten, Mode currMode);
};
