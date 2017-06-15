#include "Event.h"

Event::Event()
{
	this->nrOfEvents = 2;
}

Event::~Event()
{

}

void Event::generateEvent(Character &character)
{
	int i = rand() % this->nrOfEvents;

	switch (i)
	{
	case 0:
		//Enemy encounter
		enemyEncouter(character);
		break;
	case 1:
		//Puzzle
		puzzleEncouter(character);
		break;
	case 2:
		break;

	default:
		break;
	}
}

//Different events
void Event::enemyEncouter(Character &character)
{
	//while()
}

void Event::puzzleEncouter(Character &character)
{
	bool completed = false;
	int userAns = 0;
	int chances = 3;
	//H:\ConsoleRPG\ConsoleRPG\
	
	Puzzle puzzle("Puzzles/1.txt");

	while (!completed && chances > 0)
	{
		chances--;
		std::cout << puzzle.getAsString() << "\n";

		std::cout << "\nYour ANSWER: ";
		std::cin >> userAns;
		std::cout << "\n";
	
		if (puzzle.getCorrectAns() == userAns)
		{
			completed = true;

			//GIVE USER EXP ETC AND CONTINUE
		}
	}

	if (completed)
	{
		std::cout << "CONGRATZ YOU SUCCEDED! \n";
	}
	else
	{
		std::cout << "YOU FAILED BRAH! \n";
	}
}

