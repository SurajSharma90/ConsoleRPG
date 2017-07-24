#include "Event.h"

Event::Event()
{
	this->nrOfEvents = 2;
}

Event::~Event()
{

}

void Event::generateEvent(Character &character, dArr<Enemy>& enemies)
{
	int i = rand() % this->nrOfEvents;

	switch (i)
	{
	case 0:
		//Enemy encounter
		enemyEncouter(character, enemies);
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
void Event::enemyEncouter(Character &character, dArr<Enemy>& enemies)
{
	bool playerTurn = false;
	int choice = 0;

	//Coin toss for turn
	int coinToss = rand() % 2 + 1;

	if (coinToss == 1)
		playerTurn = true;
	else
		playerTurn = false;

	//End conditions
	bool escape = false;
	bool playerDefeated = false;
	bool enemiesDefeated = false; 

	//Enemies
	int nrOfEnemies = rand() % 5 + 1;

	for (size_t i = 0; i < nrOfEnemies; i++)
	{
		enemies.push(Enemy(character.getLevel() + rand()%3));
	}

	//Battle variables
	int damage = 0;
	int gainExp = 0;
	int gainGold = 0;
	int playerTotal = 0;
	int enemyTotal = 0;
	int combatTotal = 0;
	int combatRollPlayer = 0;
	int combatRollEnemy = 0;

	while (!escape && !playerDefeated && !enemiesDefeated)
	{
		if (playerTurn && !playerDefeated)
		{
			//Menu
			//system("CLS");

			cout << "= PLAYER TURN =" << "\n\n";
			cout << "Continue..." << "\n\n";
			cin.get();
			system("CLS");

			cout << "= BATTLE MENU =" << "\n\n";
			cout << "HP: " << character.getHP() << " / " << character.getHPMax() << "\n\n";

			cout << "0: Escape" << "\n";
			cout << "1: Attack" << "\n";
			cout << "2: Defend" << "\n";
			cout << "3: Use Item" << "\n";
			cout << "\n";

			cout << "Choice: ";

			cin >> choice;

			while (cin.fail() || choice > 3 || choice < 0)
			{
				system("CLS");

				cout << "Faulty input!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');		

				cout << "= BATTLE MENU =" << "\n\n";

				cout << "0: Escape" << "\n";
				cout << "1: Attack" << "\n";
				cout << "2: Defend" << "\n";
				cout << "3: Use Item" << "\n";
				cout << "\n";

				cout << "Choice: ";
				cin >> choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";

			//Moves
			switch (choice)
			{
			case 0: //ESCAPE
				escape = true;
				break;

			case 1: //ATTACK

				//Select enemy
				cout << "Select enemy: " << "\n\n";

				for (size_t i = 0; i < enemies.size(); i++)
				{
					cout << i << ": "
						<< "Level: " << enemies[i].getLevel() << " - " <<
						"HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() << " - " <<
						"Defence: " << enemies[i].getDefence() << " - " <<
						"Accuracy: " << enemies[i].getAccuracy() << " - " <<
						"Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() <<
						"\n";
				}

				cout << "\n";
				cout << "Choice: ";

				cin >> choice;

				while (cin.fail() || choice >= enemies.size() || choice < 0)
				{
					cout << "Faulty input!" << "\n";
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Select enemy: " << "\n\n";
					cout << "Choice: ";
					cin >> choice;
				}

				cin.ignore(100, '\n');
				cout << "\n";

				//Attack roll
				combatTotal = enemies[choice].getDefence() + character.getAccuracy();
				enemyTotal = enemies[choice].getDefence() / (double)combatTotal * 100;
				playerTotal = character.getAccuracy() / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollEnemy = rand() % enemyTotal + 1;

				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Enemy roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer > combatRollEnemy) //Hit
				{
					cout << "HIT! " << "\n\n";
					
					damage = character.getDamage();
					enemies[choice].takeDamage(damage);

					cout << "Damage: " << damage << "!" << "\n\n";

					if (!enemies[choice].isAlive())
					{
						cout << "ENEMY DEFEATED!" << "\n\n";
						gainExp = enemies[choice].getExp();
						character.gainExp(gainExp);
						gainGold = rand() % enemies[choice].getLevel() * 10 + 1;
						character.gainGold(gainGold);
						cout << "EXP GAINED: " << gainExp << "\n";
						cout << "GOLD GAINED: " << gainGold << "\n\n";



 						enemies.remove(choice);
					}
				}
				else //Miss
				{
					cout << "MISSED! \n\n";
				}

				break;

			case 2: //DEFEND

				break;

			case 3: //ITEM

				break;

			default:
				break;
			}

			//End turn
			playerTurn = false;
		}
		else if(!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
		{
			cout << "= ENEMY TURN =" << "\n";

			cout << "Continue..." << "\n\n";		
			cin.get();
			system("CLS");

			//Enemy attack
			for (size_t i = 0; i < enemies.size(); i++)
			{
				cout << "Continue..." << "\n\n";
				cin.get();
				system("CLS");
				
				cout << "Enemy: " << i << "\n\n";

				//Attack roll
				combatTotal = enemies[i].getAccuracy() + character.getDefence();
				enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
				playerTotal = character.getDefence() / (double)combatTotal * 100;
				combatRollPlayer = rand() % playerTotal + 1;
				combatRollEnemy = rand() % enemyTotal + 1;

				cout << "Player roll: " << combatRollPlayer << "\n";
				cout << "Enemy roll: " << combatRollEnemy << "\n\n";

				if (combatRollPlayer < combatRollEnemy) //Hit
				{
					cout << "HIT! " << "\n\n";

					damage = enemies[i].getDamage();
					character.takeDamage(damage);

					cout << "Damage: " << damage << "!" << "\n";
					cout << "HP: " << character.getHP() << " / " << character.getHPMax() << "\n\n";

					if (!character.isAlive())
					{
						cout << "YOU ARE DEFEATED!" << "\n\n";
						playerDefeated = true;
					}
				}
				else //Miss
				{
					cout << "MISSED! \n\n";
				}
			}

			//End turn
			playerTurn = true;
		}

		//Conditions
		if (!character.isAlive())
		{
			playerDefeated = true;
		}
		else if (enemies.size() <= 0)
		{
			enemiesDefeated = true;
		}
	}
}

void Event::puzzleEncouter(Character &character)
{
	bool completed = false;
	int userAns = 0;
	int chances = 3;
	int gainExp = (chances * character.getLevel() * (rand()%10 + 1));
	int gainGold = (chances * character.getLevel() * (rand() % 10 + 1));
	//H:\ConsoleRPG\ConsoleRPG\
	
	Puzzle puzzle("Puzzles/1.txt");

	while (!completed && chances > 0)
	{
		std::cout << "Chances: " << chances << "\n\n";
		chances--;
		std::cout << puzzle.getAsString() << "\n";

		cout << "\nYour ANSWER: ";
		cin >> userAns;

		while (cin.fail())
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\nYour ANSWER: ";
			cin >> userAns;				
		}
		
		cin.ignore(100, '\n');
		cout << "\n";

		if (puzzle.getCorrectAns() == userAns)
		{
			completed = true;

			character.gainExp(gainExp);
			character.gainExp(gainGold);
			std::cout << "YOU GAINED " << gainExp << " EXP!" << "\n";
			std::cout << "YOU GAINED " << gainGold << " GOLD!" << "\n\n";
		}
	}

	if (completed)
	{
		std::cout << "CONGRATZ YOU SUCCEDED! \n\n";
	}
	else
	{
		std::cout << "YOU FAILED BRAH! \n\n";
	}
}

