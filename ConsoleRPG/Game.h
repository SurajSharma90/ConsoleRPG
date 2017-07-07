#pragma once

#include"Functions.h"
#include"Event.h"
#include<ctime>
#include<vector>
#include<sstream>

using namespace std;

class Game
{
public:
	Game();
	virtual ~Game();

	//Operators

	//Functions
	void initGame();
	void mainMenu();
	void createNewCharacter();
	void levelUpCharacter();
	void saveCharacters();
	void loadCharacters();
	void Travel();

	//Accessors
	inline bool getPlaying() const { return this->playing; }

	//Modifiers

private:
	int choice;
	bool playing;

	//Character related
	int activeCharacter;
	std::vector<Character> characters;
	std::string fileName;
};

