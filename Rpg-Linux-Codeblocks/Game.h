#pragma once

#include"STLINCLUDE.h"

#include"Event.h"

using namespace std;

class Game
{
private:
	int choice;
	bool playing;

	//Character related
	int activeCharacter;
	std::vector<Character> characters;
	std::string fileName;

	//Enemies
	dArr<Enemy> enemies;

public:
	Game();
	virtual ~Game();

	//Operators

	//Functions
	void initGame();
	void mainMenu();
	void createNewCharacter();
	void levelUpCharacter();
	void characterMenu();
	void saveCharacters();
	void loadCharacters();
	void selectCharacter();
	void travel();
	void rest();

	//Accessors
	inline bool getPlaying() const { return this->playing; }

	//Modifiers
};

