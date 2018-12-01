#pragma once

#include"STLINCLUDE.h"

#include"Character.h"
#include"Enemy.h"
#include"Puzzle.h"
#include"Boss.h"


class Event
{
private:

public:
	Event();
	virtual ~Event();
	void generateEvent(Character &character, dArr<Enemy>& enemies);

	//Events
	void shopEncouter(Character &character);
	void enemyEncouter(Character &character, dArr<Enemy>& enemies);
	void puzzleEncouter(Character &character);
	void bossEncouter(Character &character, Boss & boss);

	//statics
	static int nrOfEvents;
};



