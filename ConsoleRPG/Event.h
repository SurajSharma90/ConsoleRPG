#pragma once

#include"Character.h"
#include"Puzzle.h"
#include<stdlib.h>
#include"dArr.h"

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

