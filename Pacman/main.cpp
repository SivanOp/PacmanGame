#include "Game.h"
#include "General.h"
#include "InputParser.h"
using namespace std;

void main(int argc,char** argv)
{
	srand(time(nullptr));

	InputParser input(argc, argv); 
	Mode currMode;
	bool nextScreen = false;
	Game game;
	int cols=0, rows=0;
	bool stillPlaying = true;
	Board board;
	Position legendPos;
	
	vector<string> screenFiles; //vector to save all the files in folder ends with .screen
	vector<Position> tunnelsPos; //vector to save all the tunnels position in the given board

    getFiles(screenFiles); 

	if (screenFiles.size() == 0)
	{
		cout << "Error! No files found in folder..." << endl;
		return;
	}

	if (argc == 1) //simple mode
	{
		currMode = (Mode)0;
	}
	else
	{
		if (input.cmdOptionExists("-load") and input.cmdOptionExists("-silent"))
			currMode = (Mode)3;
		else if (input.cmdOptionExists("-load"))
			currMode = (Mode)1;
		else if(input.cmdOptionExists("-save"))
			currMode = (Mode)2;	
	}	

	game.printMenu(false, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode);
}

