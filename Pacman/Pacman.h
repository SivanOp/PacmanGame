#pragma once
#include <iostream>
#include "Creature.h"

using namespace std;

struct Legend
{
	int amount;
	Position pos;
};

class Pacman : public Creature
{
private:
	Legend lives;
	Legend scoreShown;

public:
	//Constractor:
	Pacman();
	Pacman(int x, int y);

	//getters:
	Legend getScore() const { return scoreShown; }
	Legend getLives() const { return lives; }

	//setters:
	void setScore() { scoreShown.amount++; }
	void bonusFruit(int bonus) { scoreShown.amount+= bonus; }
	void setLives() { lives.amount = lives.amount - 1; }
	void setLives(int newLives) { lives.amount = newLives; }
	void setScorePos(Position& position) { scoreShown.pos = position; }
	void setLivesPos(Position& position) { lives.pos = position; }
	void setPacPos(int x, int y) { creaturePos.setPosition(x, y); }
};
