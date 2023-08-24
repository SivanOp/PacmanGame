#include "board.h"

using namespace std;

void Board::setBoard(bool colorChoice, int i, int j)
{
	int cols, rows;

	for (rows = 0; rows < i; rows++)
	{
		for (cols = 0; cols < j; cols++)
		{
			if (board[rows][cols] == '%')
				board[rows][cols] = ' ';

		   else if (board[rows][cols] == ' ')
			   board[rows][cols] = '.';
		}
	}

	countBreadCrumbs(i, j);
}

void Board::printBoard(bool colorChoice, int i, int j)
{
	int rows, cols;
	if (colorChoice)
		system("Color 01");

	for (rows = 0; rows < i; rows++)
	{
		for (cols = 0; cols < j; cols++)
		{

			if (board[rows][cols] == '#') //printing the walls in another color
			{
				if (colorChoice)
					textcolor(01);
				else
					textcolor(07);
			}

			else if (board[rows][cols] == '.')
			{
			   if (colorChoice)
				   textcolor(04);
			   else
				   textcolor(07);
			}
			cout << board[rows][cols];
		}
		cout << endl;
	}
	cout << endl;
}

//this function counts the amount of breadcrumbs on the board
void Board::countBreadCrumbs(int rows, int cols)
{
	int i, j;
	int count = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (board[i][j] == '.')
				count++;
		}
	}
	maxScore = count;
}

