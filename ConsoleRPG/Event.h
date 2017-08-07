#pragma once

#include"STLINCLUDE.h"

#include"Character.h"
#include"Enemy.h"
#include"Puzzle.h"


class Event
{
private:
	int nrOfEvents;

public:
	Event();
	virtual ~Event();
	void generateEvent(Character &character, dArr<Enemy>& enemies);

	//Events
	void enemyEncouter(Character &character, dArr<Enemy>& enemies);
	void puzzleEncouter(Character &character);
};

