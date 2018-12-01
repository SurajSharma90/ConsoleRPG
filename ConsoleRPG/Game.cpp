#include "Game.h"

Game::Game()
{
	choice = 0;
	playing = true;
	activeCharacter = 0;
	fileName = "characters.txt";
}

Game::~Game()
{

}

//Functions
void Game::initGame()
{
	ifstream in;
	in.open("characters.txt");

	Weapon::initNames();
	Armor::initNames();

	if (in.is_open())
		this->loadCharacters();
	else
	{
		createNewCharacter();
		this->saveCharacters();
	}

	in.close();	
}

void Game::mainMenu()
{
	cout << "ENTER to continue..." << "\n";
	cin.get();
	system("CLS");

	if (this->characters[activeCharacter].isAlive())
	{
		if (this->characters[activeCharacter].getExp() >=
			this->characters[activeCharacter].getExpNext())
		{
			cout << "LEVEL UP AVAILABLE! \n\n";
		}

		cout << "= MAIN MENU =" << "\n" << "\n";

		cout << "= Active character: " <<
			this->characters[activeCharacter].getName() << " Nr: " <<
			this->activeCharacter + 1 << "/" << this->characters.size() <<
			" =" << "\n" << "\n";

		cout << "0: Quit" << "\n";
		cout << "1: Travel" << "\n";
		cout << "2: Level up" << "\n";
		cout << "3: Rest" << "\n";
		cout << "4: Character sheet" << "\n";
		cout << "5: Create new character" << "\n";
		cout << "6: Select character" << "\n";
		cout << "7: Save characters" << "\n";
		cout << "8: Load characters" << "\n";

		cout << "\n";

		cout << "\n" << "Choice: ";
		cin >> this->choice;

		while (cin.fail() || this->choice > 9)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n" << "Choice (0 - 8): ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 0: //QUIT
			playing = false;
			this->saveCharacters();

			break;

		case 1: //TRAVEL
			travel();

			break;

		case 2: //LEVEL UP
			this->levelUpCharacter();

			break;

		case 3: //REST
			rest();

			break;

		case 4: //CHAR SHEET
			this->characterMenu();
			break;

		case 5: //CREATE NEW CHAR
			createNewCharacter();
			saveCharacters();
			break;

		case 6: //SELECT CHAR
			selectCharacter();
			break;

		case 7: //SAVE CHARS
			saveCharacters();
			break;

		case 8: //LOAD CHARS
			loadCharacters();
			break;

		default:
			break;
		}
	}
	else
	{
		cout << "= YOU ARE DEAD, LOAD? =" << "\n" << "\n";
		cout << "(0) Yes, (1) No " << "\n";
		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 1)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');
			
			cout << "(0) Yes, (1) No " << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 0)
			this->loadCharacters();
		else
			playing = false;
	}
}

void Game::createNewCharacter()
{
	string name = "";
	cout << "Character name: ";
	getline(cin, name);

	for (size_t i = 0; i < this->characters.size(); i++)
	{
		while (name == this->characters[i].getName())
		{
			cout << "Error! Character already exists!" << "\n";
			cout << "Character name: ";
			getline(cin, name);
		}
	}

	characters.push_back(Character());
	activeCharacter = characters.size() - 1;
	characters[activeCharacter].initialize(name);
}

void Game::levelUpCharacter()
{
	this->characters[activeCharacter].levelUp();

	if (this->characters[activeCharacter].getStatPoints() > 0)
	{
		cout << "You have statpoints to allocate!" << "\n\n";

		cout << "Stat to upgrade: " << "\n";
		cout << "0: Strength " << "\n";
		cout << "1: Vitality " << "\n";
		cout << "2: Dexterity " << "\n";
		cout << "3: Intelligence " << "\n";

		cin >> this->choice;

		while (cin.fail() || this->choice > 3)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Stat to upgrade: " << "\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 0: //STRENGTH
			this->characters[activeCharacter].addToStat(0, 1);
			break;

		case 1://VITALITY
			this->characters[activeCharacter].addToStat(1, 1);
			break;

		case 2://DEXTERITY
			this->characters[activeCharacter].addToStat(2, 1);
			break;

		case 3://INTELLIGENCE
			this->characters[activeCharacter].addToStat(3, 1);
			break;

		default:

			break;
		}
	}
}

void Game::characterMenu()
{
	do
	{
		system("CLS");
		cout << gui::menu_title("CHARACTER MENU");

		cout << gui::menu_divider();

		characters[activeCharacter].printStats();

		cout << gui::menu_divider();

		cout << "= MENU =" << "\n";
		cout << gui::menu_item(0, "Back");
		cout << gui::menu_item(1, "Print Inventory");
		cout << gui::menu_item(2, "Equip Item");
		cout << "\n";
		cout << "Choice: ";

		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 2)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "= MENU =" << "\n";
			cout << "0: Back" << "\n";
			cout << "1: Print Inventory" << "\n";
			cout << "2: Equip Item" << "\n";
			cout << "\n";
			cout << "Choice: ";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		switch (this->choice)
		{
		case 1:
			cout << this->characters[this->activeCharacter].getInvAsString();

			break;

		case 2:
			cout << this->characters[this->activeCharacter].getInvAsString();
			
			cout << "Item index: ";
			cin >> this->choice;

			while (cin.fail() || this->choice < 0 || this->choice >= this->characters[this->activeCharacter].getInventorySize())
			{
				cout << "Faulty input!" << "\n";
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Item index: ";
				cin >> this->choice;
			}

			cin.ignore(100, '\n');
			cout << "\n";
			
			this->characters[this->activeCharacter].equipItem(this->choice);

			break;
		default:
			break;
		}

		if (this->choice > 0)
		{
			cout << "ENTER to continue..." << "\n";
			cin.get();
		}
	
	} while (this->choice > 0);
}

void Game::saveCharacters()
{
	ofstream outFile(fileName);

	if (outFile.is_open())
	{
		for (size_t i = 0; i < this->characters.size(); i++)
		{
			outFile << this->characters[i].getAsString() << "\n";
			outFile << this->characters[i].getInvAsStringSave() << "\n";	
		}
	}

	outFile.close();
}

void Game::loadCharacters()
{
	ifstream inFile(fileName);

	this->characters.clear();

	string name = "";
	int distanceTravelled = 0;
	int gold = 0;
	int level = 0;
	int exp = 0;
	int strength = 0;
	int vitality = 0;
	int dexterity = 0;
	int intelligence = 0;
	int hp = 0;
	int stamina = 0;
	int statPoints = 0;

	//Item
	int itemType = 0;
	int defence = 0;
	int type = 0;
	int damageMin = 0;
	int damageMax = 0;
	//name
	//level
	int buyValue = 0;
	int sellValue = 0;
	int rarity = 0;

	Inventory tempItems;

	string line = "";
	stringstream str;

	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			str.str(line);
			str >> name;	
			str >> distanceTravelled;
			str >> gold;
			str >> level;
			str >> exp;
			str >> strength;
			str >> vitality;
			str >> dexterity;
			str >> intelligence;
			str >> hp;
			str >> stamina;
			str >> statPoints;

			//Create characyer
			Character temp(name, distanceTravelled, gold, level,
				exp, strength, vitality, dexterity, intelligence,
				hp, stamina, statPoints);

			//Weapon
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				damageMin >> damageMax;

			Weapon weapon(damageMin, damageMax, name, level, buyValue, sellValue, rarity);	

			//Armor head
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_head(type, defence, name, level, buyValue, sellValue, rarity);

			//Armor chest
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_chest(type, defence, name, level, buyValue, sellValue, rarity);	

			//Armor arms
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >>sellValue >>
				defence >> type;

			Armor armor_arms(type, defence, name, level, buyValue, sellValue, rarity);

			//Armor legs
			str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type;

			Armor armor_legs(type, defence, name, level, buyValue, sellValue, rarity);

			temp.setWeapon(weapon);
			temp.setArmorHead(armor_head);
			temp.setArmorChest(armor_chest);
			temp.setArmorArms(armor_arms);
			temp.setArmorLegs(armor_legs);

			//Add Inventory Items
			str.clear();
			line.clear();
			getline(inFile, line);
			
			str.str(line);

			while (str >> 
				itemType >> name >> level >> 
				rarity >> buyValue >> sellValue >> 
				damageMin >> damageMax)
			{
				temp.addItem(
					Weapon
					(
						damageMin,
						damageMax,
						name,
						level,
						buyValue,
						sellValue,
						rarity
					)
				);
			}

			str.clear();
			line.clear();
			getline(inFile, line);

			str.str(line);

			while (str >>
				itemType >> name >> level >>
				rarity >> buyValue >> sellValue >>
				defence >> type)
			{
				temp.addItem(
					Armor
					(
						type,
						defence,
						name,
						level,
						buyValue,
						sellValue,
						rarity
					)
				);
			}

			this->characters.push_back(Character(temp));

			cout << "Character " << temp.getName() << " loaded!\n";
		
			str.clear();
		}
	}

	inFile.close();

	if (this->characters.size() <= 0)
	{
		throw "ERROR! NO CHARACTERS LOADED OR EMPTY FILE!";
	}
}

void Game::selectCharacter()
{
	cout << "Select character: " << "\n\n";

	for (size_t i = 0; i < this->characters.size(); i++)
	{
		cout << "Index: " << i << " = " << this->characters[i].getName() << " Level: " << this->characters[i].getLevel() << "\n";
	}

	cout << "\n";

	cout << "Choice: ";

	cin >> this->choice;

	while (cin.fail() || this->choice >= this->characters.size() || this->choice < 0)
	{
		cout << "Faulty input!" << "\n";
		cin.clear();
		cin.ignore(100, '\n');

		cout << "Select character: " << "\n";
		cin >> this->choice;
	}

	cin.ignore(100, '\n');
	cout << "\n";

	this->activeCharacter = this->choice;

	cout << this->characters[this->activeCharacter].getName() << " is SELECTED!" << "\n\n";
}

void Game::travel()
{
	this->characters[activeCharacter].travel();

	Event ev;

	ev.generateEvent(this->characters[activeCharacter], this->enemies);
}

void Game::rest()
{
	int restCost = this->characters[this->activeCharacter].getHPMax() - this->characters[this->activeCharacter].getHP();
	cout << "= REST =" << "\n\n";
	cout << "Resting costs you: " << restCost << "\n";
	cout << "Your gold: " << this->characters[this->activeCharacter].getGold() << "\n";
	cout << "HP: " << this->characters[this->activeCharacter].getHP() << " / " << this->characters[this->activeCharacter].getHPMax() << "\n\n";

	if (this->characters[this->activeCharacter].getGold() < restCost)
	{
		cout << "NOT ENOUGH MONEY, SORRY BUDDY!" << "\n\n";
	}
	else if (this->characters[this->activeCharacter].getHP() >= this->characters[this->activeCharacter].getHPMax())
	{
		cout << "ALREADY AT FULL HEALTH BUDDY!" << "\n\n";
	}
	else
	{
		cout << "\n\n Rest? (0) Yes, (1) No..." << "\n\n";

		cin >> this->choice;

		while (cin.fail() || this->choice < 0 || this->choice > 1)
		{
			cout << "Faulty input!" << "\n";
			cin.clear();
			cin.ignore(100, '\n');

			cout << "\n\n Rest? (0) Yes, (1) No..." << "\n\n";
			cin >> this->choice;
		}

		cin.ignore(100, '\n');
		cout << "\n";

		if (this->choice == 0)
		{
			this->characters[this->activeCharacter].resetHP();
			this->characters[this->activeCharacter].payGold(restCost);
			cout << "RESTED!" << "\n\n";
		}
		else
		{
			cout << "MAYBE NEXT TIME!" << "\n\n";
		}
	}
}