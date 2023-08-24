#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>
#include <fstream>
#include "Board.h"
#include "Creature.h"
#include "Pacman.h"

enum class Mode { simple, load, save, LoadSilent };

using namespace std;

//for the files load
namespace fs = std::filesystem;
using std::ifstream;

void getFiles(vector<string>& screenFiles);
void sortFilesLex(vector<string>& screenFiles);
void readScreenFromFile(Board& board, string fileName, int& j, int& i, vector <Position>& tunnelsPos, Position& legendPos);
char* setFilesName(string screenFileName, string str);
bool checkBoardValid(Board& board, int rows, int cols);
