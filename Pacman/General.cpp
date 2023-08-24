#include "General.h"


//this function search in the directory for all the files ends with .screen
void getFiles(vector<string>& screenFiles)
{
	for (const auto& entry : fs::directory_iterator("."))
	{
		if (entry.path().string().ends_with("screen")) {
			screenFiles.push_back(entry.path().string());
		}
	}
}

//this function sorts the files found in the directory by lexicographic order
void sortFilesLex(vector<string>& screenFiles)
{
	sort(screenFiles.begin(), screenFiles.end());
}

//this function gets a file name to load, and reads all the board characters to the screen
void readScreenFromFile(Board& board, string fileName, int& j, int& i, vector <Position>& tunnelsPos, Position& legendPos)
{
	fstream currScreen(fileName, ios::in);
	if (!currScreen) // in case file not found
	{
		cout << "oooops! can't find the file! :( " << endl;
		exit(1);
	}

	string line, prevLine;
	i = 0, j = 0;
	int x, y;
	int tunnelInd;
	int colSize;

	getline(currScreen, line);
	colSize = line.size();

	while (!currScreen.eof()) 
	{
		for (i = 0; i < colSize; i++)
		{
			if (j == 0 && (line[i] == ' ' || line[i] == '%')) // in case of tunnel in first row
				tunnelsPos.push_back(Position(j, i));

			if (i == 0 && (line[i] == ' ' || line[i] == '%'))
				tunnelsPos.push_back(Position(j, i)); // in case of tunnel in first column

			if(i == colSize -1 && (line[i]== ' ' || line[i] == '%'))
				tunnelsPos.push_back(Position(j, i)); // in case of tunnel in last column
			
			if (line[i] == '&') //sets the legend position
			{
				legendPos.setPosition(i,j); 
			}
			board.setCoord(i,j, line[i]);
		}
		j++;
		prevLine = line;
		getline(currScreen, line);
	}

	// in case of tunnel in last row
	for (i = 0; i < colSize; i++)
	{
		if (prevLine[i] == ' ' || prevLine[i] == '%')
			tunnelsPos.push_back(Position(j, i)); // in case of tunnel in last column
	}

	//handling the last line in file
	for (i = 0; i < colSize; i++)
	{
		if (line[i] == '&')
		{
			legendPos.setPosition(i,j);
			board.setCoord(i, j, '&');
		}
		else
			board.setCoord(i,j, '%');
	} 

	//sets the legend position to be empty on 3 lines height * 20 characters
	for (x = 0; x < 3; x++)
	{
		for (y = 0; y < 20; y++)
		{
			board.setCoord(legendPos.getPosX() + y, legendPos.getPosY() + x, '%');
		}
	}

	board.setCoord(legendPos.getPosX(), legendPos.getPosY(),'&');
	i = colSize;
	currScreen.close();
}

//this function returns a new file name- adding str after the . in fileName 
char* setFilesName(string screenFileName,string str)
{
	int i = 1;
	const char* screenName = screenFileName.c_str();
	char* res = new char[strlen(screenName)+8]; 

	res[0] = screenName[0];
	while (screenName[i] != '.')
	{
		res[i] = screenName[i];
		i++;
	}
	res[i] = '\0';
	strcat(res, str.c_str());
	return res;
}

//this function checks if the screen loaded from file is valid
bool checkBoardValid(Board& board, int rows, int cols)
{
	int i,j, ghostCounter=0, pacmanCounter=0,legendCounter=0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (board.getCoord(j, i) == '$')
			{
				ghostCounter++;
			}
			if (board.getCoord(j, i) == '@')
			{
				pacmanCounter++;
				
			}
			if (board.getCoord(j, i) == '&')
			{
				legendCounter++;
				if (i <= rows || j <= cols)
				{
					cout << "legend position is invalid!" << endl;
					return false;
				}
			}
				
			if (board.getCoord(j, i) != '@' && board.getCoord(j, i) != '$' && board.getCoord(j, i) != '#' && board.getCoord(j, i) != '&' && board.getCoord(j, i) != '%' && board.getCoord(j, i) != ' ')
			{
				cout << "invalid character " << board.getCoord(j, i) <<  endl;
				return false;
			}
				
		}
	}
	if (pacmanCounter > 1)
	{
		cout << "more than one pacman on board!" << board.getCoord(j, i) << endl;
		return false;
	}

	else if (pacmanCounter == 0)
	{
		cout << "no pacman on board!" << board.getCoord(j, i) << endl;
		return false;
	}

	if (ghostCounter > 4)
	{
		cout << "number of ghosts is bigget than 4! there are " << ghostCounter<< " ghosts on board!" << endl;
		return false;
	}

	


}

