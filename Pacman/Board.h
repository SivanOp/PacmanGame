#pragma once
#pragma once
#include <iostream>
#include "Color.h"

const int length = 80;
const int width = 25;

class Board
{

private:

	char board[width][length] = { " " };
	 int maxScore;

public:
	//Getters:
	char getCoord(int x, int y) const { return board[y][x]; }
	int getMaxScore() const { return maxScore; }

	//Setters:
	void setCoord(const int& x, const int& y, const char& ch) { board[y][x] = ch; } 
	void setMaxScore(int& score) { maxScore = score; }

	//Functions:
	void setBoard(bool colorChoice, int i, int j);
	void printBoard(bool colorChoice, int i, int j);
	void countBreadCrumbs(int rows, int cols);
};