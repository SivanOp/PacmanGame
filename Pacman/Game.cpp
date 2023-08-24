#include "Game.h"

//this function updates the pacman coordinate by the key that the user pressed
void Game::updateCoordByKey(char keyPressed, Pacman& pacman, int xPos, int yPos)
{
	switch (keyPressed)
	{
	case 'A':
	case 'a':
		pacman.setPos(Position(xPos - 1, yPos));
		pacman.setDir((Direction)LEFT);
		break;
	case 'D':
	case 'd':
		pacman.setPos(Position(xPos + 1, yPos));
		pacman.setDir((Direction)RIGHT);
		break;
	case 'W':
	case 'w':
		pacman.setPos(Position(xPos, yPos - 1));
		pacman.setDir((Direction)UP);
		break;
	case 'X':
	case 'x':
		pacman.setPos(Position(xPos, yPos + 1));
		pacman.setDir((Direction)DOWN);
		break;
	case 'S':
	case 's':
		break;
	default:
		keyPressed = 's';
	}

}

//this function handles the breadCrumbs inside the tunnel and updates the score
void Game::tunnelMove(Position& pacPos, Position& pacPrevPos, Pacman& pacman, Board& board, int& breadcrumbsEaten, Mode currMode)
{
	board.setCoord(pacPrevPos.getPosX(), pacPrevPos.getPosY(), ' ');
	if ((int)currMode != 3)
	{
		cout << board.getCoord(pacPrevPos.getPosX(), pacPrevPos.getPosY()) << endl;
		pacman.getPos().gotoxy();
		
	}
	
	if (board.getCoord(pacPos.getPosX(), pacPos.getPosY()) == '.') //Pacman ate breadcrump in the tunnel
	{
		pacman.setScore();
		breadcrumbsEaten++;
	}
	if ((int)currMode != 3)
		cout << board.getCoord(pacman.getPos().getPosX(), pacman.getPos().getPosY()) << endl;
	pacman.getPos().setPosition(pacPos.getPosY(), pacPos.getPosX()); 
}

//this function checks if the pacman ate all the breadCrumbs on the board
bool Game::checkWin(Board& board, int breadcrumbsEaten, Mode currMode)
{
	if (breadcrumbsEaten == board.getMaxScore())
	{
		if ((int)currMode != 3)
		{
			system("cls");
			textcolor(07);
			cout << "Congragulations! You Won the Game!!!" << endl << endl;
			Sleep(1000);
		}
		return true;
	}
	return false;
}

//this function checks if the pacman has no lives
bool Game::checkLose(Pacman& pacman, Mode currMode)
{
	if (pacman.getLives().amount == 0)
	{
		if ((int)currMode != 3)
		{
			system("cls");
			cout << "YOU LOST THE GAME :( " << endl << endl;
		}
		return true;
	}
	return false;
}

//this function checks if the ghost position colides with the pacman position
bool Game::checkColisionPG(Position& pacPos, vector<Ghost>& ghosts)
{
	for (int i = 0; i < ghosts.size(); i++)
	{
		if (ghosts[i].getPos() == pacPos)
			return true;
	}
	return false;
}
//this function checks if the pacman position colides with the fruit position and sets the score
bool Game::checkColisionPF(Fruit& fruit, Position& fruitPos, Pacman& pacman, Board& board)
{
	if (fruitPos == pacman.getPos())
	{
		pacman.bonusFruit(fruit.getShape() - '0');
		return true;
	}
	else
		return false;
}
//this function checks if the ghost position colides with the fruit position
bool Game::checkColisionGF(Position& fruitPos, vector<Ghost>& ghosts)
{
	for (int i = 0; i < ghosts.size(); i++)
	{
		if (ghosts[i].getPos() == fruitPos)
			return true;
	}
	return false;
}

//this function checks if the pacman entered a tunnel, and updates the pacman position
void Game::Tunnels(Pacman& pacman, vector<Position>&tunnelsPos, Position& pacPrevPos,Board& board, int rows, int cols,int& breadcrumbsEaten, Mode currMode)
{
	Position currTunnelPos;
	int i;
	//check if the pacman entered into a tunnel
	for (i = 0; i < tunnelsPos.size(); i++)
	{
		if ((pacman.getPos().getPosX() == tunnelsPos[i].getPosY()) && (pacman.getPos().getPosY() == tunnelsPos[i].getPosX()))
		{
			if (tunnelsPos[i].getPosX() == 0)
			{
				currTunnelPos.setPosition(rows - 1, pacman.getPos().getPosX());
				tunnelMove(currTunnelPos, pacPrevPos, pacman, board, breadcrumbsEaten,currMode);
				break;
			}
			else if (tunnelsPos[i].getPosY() == 0)
			{
				currTunnelPos.setPosition(pacman.getPos().getPosY(), cols - 1);
				tunnelMove(currTunnelPos, pacPrevPos, pacman, board, breadcrumbsEaten, currMode);
				break;
			}
			else if (tunnelsPos[i].getPosY() == cols - 1)
			{
				currTunnelPos.setPosition(pacman.getPos().getPosY(), 0);
				tunnelMove(currTunnelPos, pacPrevPos, pacman, board, breadcrumbsEaten, currMode);
				break;
			}
			else if (tunnelsPos[i].getPosX() == rows)
			{
				currTunnelPos.setPosition(0, pacman.getPos().getPosX());
				tunnelMove(currTunnelPos, pacPrevPos, pacman, board, breadcrumbsEaten, currMode);
				break;
			}
		}
	}
}

//this function handles the fruit in load mode
void Game::fruitInLoad(Fruit& fruit,Position& prevFruit,Board& board, bool colorChoice,int rows,int cols,string line, char* dup,bool newFruit, int& dir, Mode currMode)
{
	fruit.setPrevFruit(prevFruit, board, colorChoice, currMode);

	fruit.setShape(line[0]);
	dup = _strdup(line.c_str());
	strtok(dup, " ");
	dir = stoi(strtok(nullptr, " "));
	fruit.setDir((Direction)dir);
	fruit.moveCreatureByDir((Direction)dir, board, rows, cols);

	if ((int)currMode==1 && newFruit)
	{
		textcolor(06);
		fruit.getPos().gotoxy();
		cout << fruit.getShape() << endl;
		textcolor(04);
	}
}

//this function compares the result achieved in silent mode with the result in the result file 
bool Game::checkIfGoodResult(vector<int>result, string fileName,Pacman& pacman,Board& board,int breadCrumbsEaten,Mode currMode)
{
	int i = 0 , j = 0,k;
	int res;
	string line;
	char* resfileName = setFilesName(fileName, ".result");
	fstream resFile(resfileName, ios::in);
	delete[] resfileName;

	getline(resFile, line);

	for(k=0;k<result.size();k++)
	{
		i = 0;
		if (line[0] == '(')
		{
			while (line[i] != ')')
			{
				i++;
			}
			i++;
			res = stoi(line.c_str() + i);
			if (res != result[j])
			{
				return false;
			}
			j++;
		}
		else
		{
			if (strstr(line.c_str(), "game over") != nullptr)
			{
				if (!checkLose(pacman,currMode))
					return false;
			}
			else if (strstr(line.c_str(), "passed screen") != nullptr)
			{
				if (!checkWin(board,breadCrumbsEaten,currMode))
					return false;
			}
		}
		getline(resFile, line);
	}

	return true;
}


//this function is the main loop of the game
void Game::gameLoop(char keyPressed,Pacman& pacman, Board& board, vector<Ghost>& ghosts, bool colorChoice, char levelChoice, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode, int& currScreen)
{
	bool stillPlaying = true;
	bool PGColisionFound = false;
	bool PFColisionFound = false;
	bool GFColisionFound = false;
	bool won = false, lose = false;
	int ghostStep = 0;
	int fruitStep = 1;
	char key = 0;
	int coordRes = ghost;
	int xPos, yPos;
	char isEsc;
	bool newFruit = true;
	Fruit fruit;
	Position prevFruit;
	Position pacPrevPos;
	int i;
	int pointOfTime = 0;
	int breadcrumbsEaten = 0;

	char* StepsfileName = setFilesName(screenFiles[currScreen], ".steps");
	char* resfileName = setFilesName(screenFiles[currScreen], ".result");
	ofstream stepsFile(StepsfileName);
	ofstream resFile(resfileName);
	delete[] StepsfileName;
	delete[] resfileName;
	
	xPos = pacman.getPos().getPosX();
	yPos = pacman.getPos().getPosY();

	//set fruit on board
	fruit.randomFruitNum();
	fruit.setFruitPosInBoard(board, pacman.getPos(), ghosts, rows, cols);
	fruit.printCreature(colorChoice);

	//in load mode
	if((int)currMode == 2)
		stepsFile << "A  " << fruit.getPos().getPosX() << "  " << fruit.getPos().getPosY() << endl;

	prevFruit.setPosition(fruit.getPos().getPosX(), fruit.getPos().getPosY());

	while (stillPlaying == true) 
	{
		Sleep(200);

		if (colorChoice)
			textcolor(06);
		else
			textcolor(07);

		pacman.getLives().pos.gotoxy();

		cout << "LIVES <3 : " << pacman.getLives().amount; //print the lives

		pacPrevPos.setPosition(xPos, yPos); 

		updateCoordByKey(keyPressed, pacman, xPos, yPos);

		if (newFruit)
		{
			PFColisionFound = checkColisionPF(fruit, fruit.getPos(), pacman, board);
		}
		GFColisionFound = checkColisionGF(fruit.getPos(), ghosts);
		PGColisionFound = checkColisionPG(pacman.getPos(),ghosts);

		if (!PGColisionFound) //in case the ghost didn't eat the pacman
		{
			coordRes = pacman.getPos().checkCoord(board, pacman.getPos().getPosX(), pacman.getPos().getPosY());
			//checks for the current pacPos char on the board

			if (coordRes == wall)//in case the next move of the pacman is a '#', stay
			{
				PGColisionFound = PGColisionFound || checkColisionPG(pacPrevPos, ghosts);
				if (newFruit)
				{
					PFColisionFound = PFColisionFound || checkColisionPF(fruit, prevFruit, pacman, board);
				}
				GFColisionFound = GFColisionFound || checkColisionGF(prevFruit,ghosts);
				keyPressed = 's';
			}
			
			else if ((coordRes == breadCrumbs) || (coordRes == emptySpace))//in case it is a breadCrumb or an empty space- keep moving
			{
				if (colorChoice)
					textcolor(06);
				else
					textcolor(07);

				pacman.getScore().pos.gotoxy();
				cout << "SCORE : " << pacman.getScore().amount; //print the score


				if (coordRes == breadCrumbs)//in case it is a breadCrumb - add to the score
				{
					pacman.setScore();
					breadcrumbsEaten++;
				}

				//set the prev pos of the pacman to be an empty space after he ate the breadCrumb
				board.setCoord(pacman.getPos().getPosX(), pacman.getPos().getPosY(), ' ');

				//check if the pacman entered into a tunnel
				Tunnels(pacman, tunnelsPos, pacPrevPos, board, rows, cols, breadcrumbsEaten,currMode);

				//move the pacman to a new position
				pacPrevPos.gotoxy();
				cout << " " << endl;

				pacman.getPos().gotoxy();
				cout << "@" << endl;

				xPos = pacman.getPos().getPosX();
				yPos = pacman.getPos().getPosY();

				PGColisionFound = PGColisionFound || checkColisionPG(pacman.getPos(), ghosts);
				if (newFruit)
					PFColisionFound = PFColisionFound || checkColisionPF(fruit, prevFruit, pacman, board);
				GFColisionFound = GFColisionFound || checkColisionGF(fruit.getPos(), ghosts);

			}

			if (ghostStep % 2 == 0) // move the ghosts every 2 steps of the pacman
			{
				for (i = 0; i < ghosts.size(); i++)
				{
					ghosts[i].setPrevGhost(ghosts, board, ghosts[i].getPos(), colorChoice, currMode);
				}

				for (i = 0; i < ghosts.size(); i++)
				{
					ghosts[i].moveGhost(board, levelChoice, pacman, rows, cols);
					ghosts[i].printCreature(colorChoice);
				}

				PGColisionFound = PGColisionFound || checkColisionPG(pacman.getPos(), ghosts);
				if (newFruit)
				{
					PFColisionFound = PFColisionFound || checkColisionPF(fruit, prevFruit, pacman, board);
				}		
				GFColisionFound = GFColisionFound || checkColisionGF(fruit.getPos(), ghosts);
			}

			if (GFColisionFound)
			{
				fruit.setPrevFruit(prevFruit, board, colorChoice, currMode);
				prevFruit.gotoxy();
				cout << board.getCoord(prevFruit.getPosX(), (prevFruit.getPosY())) << endl;

				newFruit = false;

				if ((int)currMode == 2)
					stepsFile << "D" << endl;
			}

			//check for collision between the pacman and the fruit only if theres a new fruit on board
			if (newFruit && PFColisionFound)
			{
				pacman.getPos().gotoxy();
				cout << "@" << endl;

				newFruit = false;

				if ((int)currMode == 2)
					stepsFile << "D" << endl;
			}

			//in case the pacman didnt eat the fruit after some time, the fruit disappears 
			if (fruitStep % 40 == 0 && !PFColisionFound)
			{
				fruit.getPos().gotoxy();
				cout << board.getCoord(fruit.getPos().getPosX(), (fruit.getPos().getPosY())) << endl;
				newFruit = false;

				if ((int)currMode == 2)
					stepsFile << "D" << endl;
			}

			//after some time the fruit appears again
			if (fruitStep % 80 == 0 && newFruit == false)
			{
				fruit.randomFruitNum();
				fruit.setFruitPosInBoard(board, pacman.getPos(), ghosts, rows,cols);
				newFruit = true;

				if ((int)currMode == 2)
					stepsFile << "A  " << fruit.getPos().getPosX() << "  " << fruit.getPos().getPosY() << endl;
			}
			//in case the pacman didnt eat the fruit and there is still a fruit on the screen
			if (!PFColisionFound && newFruit == true)
			{
				fruit.setPrevFruit(prevFruit, board, colorChoice, currMode);

				fruit.moveCreature(board, rows,cols);

				fruit.printCreature(colorChoice);
			}
			if (newFruit)
			{
				PFColisionFound = PFColisionFound || checkColisionPF(fruit, fruit.getPos(), pacman, board);	
			}
			GFColisionFound = GFColisionFound || checkColisionGF(fruit.getPos(), ghosts);
		}

		if (PGColisionFound)//in case the ghost ate the pacman
		{
			pacman.setLives();//set lives

			for (i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].setPrevGhost(ghosts, board, pacman.getPos(), colorChoice, currMode);
			}

			//the ghost and the pacman return to their start position

			pacman.setPos(pacman.getInitialPos());

			for (i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].setPos(ghosts[i].getInitialPos());
			}

			xPos = pacman.getPos().getPosX();
			yPos = pacman.getPos().getPosY();

			pacPrevPos.gotoxy();

			cout << " " << endl;

			pacman.getPos().gotoxy();
			cout << "@" << endl;


			for (i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].printCreature(colorChoice);
			}
		}

		//in save mode 
		if ((int)currMode == 2)
		{
			if (keyPressed != 's')
				stepsFile << "@  " << pacman.getDir() << endl;
			else
				stepsFile << "@  " << "4" << endl;


			pointOfTime++;

			if (ghostStep % 2 == 0)
			{
				for (int i = 0; i < ghosts.size(); i++)
				{
					stepsFile << "$" << i + 1 << " " << ghosts[i].getDir() << endl;
				}
			}

			if (newFruit)
			{
				stepsFile << fruit.getShape() << "  " << fruit.getDir() << endl;
			}
			if (PGColisionFound)
			{
				resFile << "(x_x)" << pointOfTime << endl;
				stepsFile << "PD " << pointOfTime << endl;
			}	
		}
			
		if (_kbhit()) //user changed the pacman position
		{
			isEsc = pacman.getPos().getKey();
			if (isEsc == 27) //in case user pressed Esc the game will pause
			{
				isEsc = pacman.getPos().getKey();
				while (isEsc != 27) //pressing the Esc again will continue the game
				{
					isEsc = pacman.getPos().getKey();
				}
			}
			else
				keyPressed = isEsc;
		}

		bool isWin = checkWin(board, breadcrumbsEaten, currMode);
		if (isWin || checkLose(pacman, currMode)) //if case user won the current screen, move to the next screen
		{
			stillPlaying = false;
			textcolor(07);
			cout << "Press any key to continue ..." << endl;
			if (isWin)
				nextScreen = true;

			if ((int)currMode == 2)
			{
				if (isWin)
				{
					resFile << "passed screen " << pointOfTime << endl;
					stepsFile << "PS " << pointOfTime << endl;
				}
					
				else
				{
					resFile << "game over " << pointOfTime << endl;
					stepsFile << "GO " << pointOfTime << endl;
				}
					
			}

			if (_getch())//wait for pressing a key to continue
				printMenu(colorChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode);
		}
		ghostStep++;
		fruitStep++;

	}

	resFile.close();
	stepsFile.close();
}

//this function handles the pacman in load mode
void Game:: pacInLoad(Position& pacPrevPos, Pacman& pacman, char* dup,string line,int& breadcrumbsEaten,Board& board, int& dir, vector<Position>& tunnelsPos, int rows,int cols,Mode currMode)
{
	pacPrevPos.setPosition(pacman.getPos().getPosX(), pacman.getPos().getPosY());

	dup = _strdup(line.c_str());
	strtok(dup, " ");
	dir = stoi(strtok(nullptr, " "));
	if (dir != 4)
	{
		pacman.setDir((Direction)dir);
	}
	
	Position newPosition = pacman.getCreatureNewPositionByDir(pacman.getPos(), (Direction)dir);

	int newX = newPosition.getPosX();
	int newY = newPosition.getPosY();
	pacman.setPacPos(newX, newY);

	if (board.getCoord(pacman.getPos().getPosX(), pacman.getPos().getPosY()) == '.')
	{
		breadcrumbsEaten++;
		pacman.setScore();
		//set the prev pos of the pacman to be an empty space after he ate the breadCrumb
		board.setCoord(pacman.getPos().getPosX(), pacman.getPos().getPosY(), ' ');

	}

	//check if the pacman entered into a tunnel
	Tunnels(pacman, tunnelsPos, pacPrevPos, board, rows, cols, breadcrumbsEaten,currMode);

	if ((int)currMode == 1)
	{
		pacPrevPos.gotoxy();
		cout << " " << endl;
		board.setCoord(pacPrevPos.getPosX(), pacPrevPos.getPosY(), ' ');
		textcolor(06);
		pacman.getPos().gotoxy();
		cout << "@" << endl;
		textcolor(04);
	}
}

//this function handles the ghosts in load mode
void Game::ghostInLoad(char* dup, string line, int& dir, int& ghostNum, Board& board, int rows, int cols, vector<Ghost>& ghosts, Mode currMode)
{
	dup = _strdup(line.c_str());
	strtok(dup, " ");
	dir = stoi(strtok(nullptr, " "));
	ghostNum = ((line[1] - '0') - 1);

	ghosts[ghostNum].setPrevPos(ghosts[ghostNum].getPos());
	
	if ((int)currMode == 1)
	{
		ghosts[ghostNum].getPrevPos().gotoxy();
		cout << board.getCoord(ghosts[ghostNum].getPrevPos().getPosX(), ghosts[ghostNum].getPrevPos().getPosY());
	}
		
	ghosts[ghostNum].setDir((Direction)dir);
	ghosts[ghostNum].moveCreatureByDir((Direction)dir, board, rows, cols);

	if ((int)currMode == 1)
	{
		textcolor(06);
		ghosts[ghostNum].getPos().gotoxy();
		cout << "$" << endl;
		textcolor(04);
	}
}

//game loop in load mode 
void Game::gameLoopLoad(Pacman& pacman, char colorChoice, Board& board, vector<Ghost>& ghosts, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode, int& currScreen)
{
	int i, j;
	int dir=0, ghostNum;
	Fruit fruit;
	string line;
	Position pacPrevPos, prevFruit;
	char* fileName = setFilesName(screenFiles[currScreen], ".steps");
	fstream loadFile(fileName, ios::in);
	delete[] fileName;
	bool newFruit = true;
	int breadcrumbsEaten = 1;
	bool PFColisionFound=false, GFColisionFound=false, PGColisionFound=false;
	vector<int>result;
	getline(loadFile, line);
	bool test = true;
	bool isWin = false , isLose = false;
	char* token;

	char* dup = _strdup(line.c_str());
	strtok(dup, " ");

	int fruitX = stoi(strtok(nullptr, " "));
	int fruitY = stoi(strtok(nullptr, " "));
	
	fruit.setPos(Position(fruitX, fruitY));
	getline(loadFile, line);

	while (!loadFile.eof())
	{
		if((int)currMode==1)
			Sleep(50);
		if ((int)currMode == 1)
		{
			textcolor(06);
			pacman.getScore().pos.gotoxy();
			cout << "SCORE : " << pacman.getScore().amount; //print the score

			pacman.getLives().pos.gotoxy();
			cout << "LIVES <3 : " << pacman.getLives().amount; //print the lives
			textcolor(04);
		}

		if (line[0] == '@')
		{
			pacInLoad(pacPrevPos, pacman, dup, line, breadcrumbsEaten, board, dir, tunnelsPos, rows, cols, currMode);
		}

		else if (line[0] == '$')
		{
			ghostInLoad(dup, line, dir, ghostNum, board, rows, cols, ghosts, currMode);
		}

		else if ((int)currMode==3 && line[0] == 'P' && line[1] == 'D')
		{
			result.push_back(atoi(line.substr(3).c_str()));
		}

		else if (line[0] == 'P' && line[1] == 'S')
		{
			isWin = true;
		}

		else if (line[0] == 'G' && line[1] == 'O')
		{
			isLose = true;
		}

		else if (line[0] == 'A')
		{
			dup = _strdup(line.c_str());
			strtok(dup, " ");
			fruitX = stoi(strtok(nullptr, " "));
			fruitY = stoi(strtok(nullptr, " "));
			fruit.setPos(Position(fruitX, fruitY));

			newFruit = true;
		}
		else if (line[0] == 'D')
		{
			newFruit = false;

			fruit.setPrevFruit(prevFruit, board, colorChoice, currMode);
			if ((int)currMode == 1)
			{
				prevFruit.gotoxy();
				cout << board.getCoord(prevFruit.getPosX(), (prevFruit.getPosY())) << endl;
			}
		}
		else
		{
			fruitInLoad(fruit, prevFruit, board, colorChoice, rows, cols, line, dup, newFruit, dir, currMode);
		}
		if (newFruit)
		{
			PFColisionFound = checkColisionPF(fruit, fruit.getPos(), pacman, board);
			GFColisionFound = checkColisionGF(fruit.getPos(), ghosts);
		}
		
		PGColisionFound = checkColisionPG(pacman.getPos(), ghosts);
		
		if (PGColisionFound)//in case the ghost ate the pacman
		{
			pacman.setLives();//set lives
			

			if ((int)currMode == 3 && result.size() != 0)
			{
				test = checkIfGoodResult(result, screenFiles[currScreen], pacman, board, breadcrumbsEaten, currMode);

				if (!test)
				{
					cout << "Test Failed!" << endl;
					exit(1);
				}
			}

			for (i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].setPrevGhost(ghosts, board, pacman.getPos(), colorChoice, currMode);
			}
			
			//the ghost and the pacman return to their start position

			pacman.setPos(pacman.getInitialPos());

			for (i = 0; i < ghosts.size(); i++)
			{
				ghosts[i].setPos(ghosts[i].getInitialPos());
			}

			if ((int)currMode == 1)
			{
				pacPrevPos.gotoxy();

				cout << " " << endl;
				textcolor(06);
				pacman.getPos().gotoxy();
				cout << "@" << endl;
				textcolor(04);

				for (i = 0; i < ghosts.size(); i++)
				{
					ghosts[i].printCreature(colorChoice);
				}
			}	
		}

		if (GFColisionFound)
		{
			fruit.setPrevFruit(prevFruit, board, colorChoice, currMode);
			if ((int)currMode == 1)
			{
				prevFruit.gotoxy();
				cout << board.getCoord(prevFruit.getPosX(), (prevFruit.getPosY())) << endl;
			}
			newFruit = false;
		}

		if (newFruit && PFColisionFound && (int)currMode == 1)
		{
			if (board.getCoord(prevFruit.getPosX(), prevFruit.getPosY()) == '.')
			{
				breadcrumbsEaten++;
				pacman.setScore();
				board.setCoord(pacman.getPos().getPosX(), pacman.getPos().getPosY(), ' ');
				
			}	
			textcolor(06);
			pacman.getPos().gotoxy();
			cout << "@" << endl;
			textcolor(04);
		}
		if (isWin || isLose) //in case user won the current screen, move to the next screen
		{
			if (isWin)
				nextScreen = true;
			if (isLose)
				nextScreen = false;
			if ((int)currMode == 3)
			{
				test = checkIfGoodResult(result, screenFiles[currScreen], pacman, board, breadcrumbsEaten, currMode);
				
				if (test)
					cout << "Test Passed succesfully!!!" << endl;
				else
					cout << "Test Failed!!!" << endl;
				exit(1);
			}

			printMenu(colorChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode);
			break;
		}
		getline(loadFile, line);
	}
	
	delete[] dup;	
}

//this is the start game function
void Game::startGame(Pacman& pacman, char levelChoice, Board& board, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode, int& currScreen)
{
	char keyPressed;
	int i, j, ind = 0;
	bool colorChoice = false;
	char withColor;
	vector<Ghost>ghosts;

	//sets all the creatures on board 
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (board.getCoord(j, i) == '$')
			{
				board.setCoord(j, i, '.');
				ghosts.push_back(Ghost(j, i));
				ghosts[ghosts.size() - 1].setInitialPos(Position(j, i));
			}
			if (board.getCoord(j, i) == '@')
			{
				board.setCoord(j, i, ' ');
				pacman.setPos(Position(j, i));
				pacman.setInitialPos(Position(j, i));
			}
		}
	}
	//sets the legend position
	pacman.setLivesPos(legendPos);
	Position position(legendPos.getPosX(), legendPos.getPosY() + 1);
	pacman.setScorePos(position);

	if ((int)currMode != 3)
		system("cls");
	if ((int)currMode == 0 || (int)currMode == 2)
	{
		cout << "For game with colors press Y, else press N" << endl;
		cin >> withColor;
		if (withColor == 'Y' || withColor == 'y')
			colorChoice = true;

	}
	if ((int)currMode != 3)
		system("cls");
	if((int)currMode == 1)
		colorChoice=true;

	board.setBoard(colorChoice, rows, cols);

	if((int)currMode!=3)
		board.printBoard(colorChoice, rows, cols);

	if ((int)currMode == 0 || (int)currMode == 2)
	{
		keyPressed = pacman.getPos().getKey();

		while (!pacman.getPos().check_key(keyPressed)) //the game starts if a key was pressed
			keyPressed = pacman.getPos().getKey();
		gameLoop(keyPressed, pacman, board, ghosts, colorChoice, levelChoice, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode, currScreen);
	}
	else
	{
		colorChoice = true;
		gameLoopLoad(pacman, colorChoice, board, ghosts, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode, currScreen);
	}

}

//this function prints the game instructions
void Game::printInstructions(bool colorChoice, Board& board, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode)
{
	textcolor(07); 
	char choice;
	cout << "INSTRUCTIONS:" << endl;
	cout << "You can choose a specific screen to load by name or let us choose for you." << endl;
	cout << "Note that the lives and score are saved between the screens!" << endl;
	cout << "The pacman travels on screen and eats the breadcrumbs. Each eaten breadcrumb equals a point to be earned." << endl;
	cout << "Once all breadcrumbs on screen are eaten the user wins and you can move to the next screen." << endl;
	cout << "Fruits appears on screen and can raise up the score acoording to the digit, try to eat them as a bonus points!!!! " << endl;
	cout << "the game includes 3 levels according to the ghosts - (a)BEST (b)GOOD (c)NOVICE " << endl;
	cout << "if you can escape from the smart ghosts, you are a real winner!!!!!! " << endl;
	cout << "In case a ghost eats the pacman, the player loses one life. If all lives are gone, the game is over." << endl;
	cout << "KEYS:" << endl;
	cout << "To move the pacman press the following keys:" << endl;
	cout << "LEFT:  A or a" << endl;
	cout << "RIGHT: D or d" << endl;
	cout << "UP:    W or w" << endl;
	cout << "DOWN:  X or x" << endl;
	cout << "STAY:  S or s" << endl;
	cout << "To pause the game you can press at any level the 'Esc' key" << endl;
	cout << "To return to the menu press any key" << endl;
	cout << "Good luck!!! :)" << endl;
	cin >> choice;
	printMenu(colorChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles,nextScreen,currMode);
}

//this function prints the menu
int Game::printMenu(bool colorChoice, Board& board, int rows, int cols, vector<Position> tunnelsPos, Position& legendPos, vector<string>& screenFiles, bool& nextScreen, Mode& currMode)
{
	static Pacman pacman;
	textcolor(07);
	if((int)currMode!=3)
		system("cls");
	int choice;
	static int currScreen = 0;
	char levelChoice = 0;
	char fileChoice;
	string fileName;
	if (nextScreen == true) //if the user won the previous screen
	{
		currScreen++;
		if (currScreen == screenFiles.size())
		{
			if ((int)currMode != 3)
			{
				cout << "No More Screens To Load!!!" << endl;
				cout << "See you next time :) " << endl;
			}
			exit(1);
		}
		
		readScreenFromFile(board, screenFiles[currScreen], rows, cols, tunnelsPos, legendPos); //load next screen from file
		
		if (!checkBoardValid(board, rows, cols))
		{
			if ((int)currMode !=3)
			{
				cout << "current screen is invalid! loading next screen..." << endl;
				system("pause");
			}
			currScreen++;
			readScreenFromFile(board, screenFiles[currScreen], rows, cols, tunnelsPos, legendPos);
		}
		if((int)currMode!=3)
			system("cls");
		if ((int)currMode == 0 || (int)currMode == 2)
		{
			cout << "Please choose one of the levels:" << endl;
			cout << "a. BEST" << endl << "b. GOOD" << endl << "c. NOVICE" << endl;
			cin >> levelChoice;
			nextScreen = false;
			
		}
		startGame(pacman, levelChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode, currScreen);
	}
	else
	{
		if (pacman.getLives().amount == 0) //in case user lost the game
		{
			if((int)currMode != 3)
				cout << "See you next time :) " << endl;
			exit(1);
		}
		if ((int)currMode == 0 || (int)currMode == 2)//simple/save mode
		{
			//print menu
			cout << "Welcome to the PACMAN GAME" << endl;
			cout << "Please choose one of the following options:" << endl;
			cout << "1. START a new game :) " << endl;
			cout << "2. Present instructions and keys " << endl;
			cout << "3. EXIT :( " << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				system("cls");
				sortFilesLex(screenFiles);
				readScreenFromFile(board, screenFiles[currScreen], rows, cols, tunnelsPos, legendPos);

				if (!checkBoardValid(board, rows, cols))
				{
					cout << "current screen is invalid! loading next screen..." << endl;
					system("pause");
					currScreen++;
					readScreenFromFile(board, screenFiles[currScreen], rows, cols, tunnelsPos, legendPos);
				}

				system("cls");
				if ((int)currMode == 0 || (int)currMode == 2)
				{
					cout << "Please choose one of the levels:" << endl;
					cout << "a. BEST" << endl << "b. GOOD" << endl << "c. NOVICE" << endl;
					cin >> levelChoice;
				}
				startGame(pacman, levelChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode, currScreen);
				break;

			case 2:
				system("cls");
				printInstructions(colorChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode);
				break;
			case 3:
			{
				system("cls");
				return 0;
			}
			}

		}
		else//in load mode
		{
			system("cls");
			sortFilesLex(screenFiles);
			readScreenFromFile(board, screenFiles[currScreen], rows, cols, tunnelsPos, legendPos);

			if (!checkBoardValid(board, rows, cols))
			{
				cout << "current screen is invalid! loading next screen..." << endl;
				system("pause");
				currScreen++;
				readScreenFromFile(board, screenFiles[currScreen], rows, cols, tunnelsPos, legendPos);
			}

			system("cls");
			startGame(pacman, levelChoice, board, rows, cols, tunnelsPos, legendPos, screenFiles, nextScreen, currMode, currScreen);
		}
	}
	
}