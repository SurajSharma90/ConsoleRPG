#include "Event.h"

int Event::nrOfEvents = 4;

;

Event::Event()
{
}

Event::~Event()
{
}

void Event::generateEvent(Character& character, std::vector<Enemy>& enemies)
{
  int i = rand() % Event::nrOfEvents;
  switch (i)
  {
    case 0:
      // Enemy encounter
      this->enemyEncouter(character, enemies);
      break;
    case 1:
      // Puzzle
      this->puzzleEncouter(character);
      break;
    case 2:
      // Shop
      this->shopEncouter(character);
      break;
    case 3:
      // Boss
      std::cout << "Boss encounter under construction..."
                << "\n";
      break;

    default:
      break;
  }
}

void Event::printShop(Inventory& inventory)
{
  std::string inv;
  for (size_t i = 0; i < inventory.size(); i++)
  {
    inv += std::to_string(i) + ": " + inventory[i]->toString() +
           "\n - PRICE: " + std::to_string(inventory[i]->getBuyValue()) + "\n";
  }

  std::cout << inv << "\n";
}

// Different events
void Event::shopEncouter(Character& character)
{
  int choice = 0;
  bool shopping = true;
  Inventory merchantInv;

  // Init merchant inv
  int nrOfItems = rand() % 20 + 10;
  bool coinToss = false;

  for (size_t i = 0; i < nrOfItems; i++)
  {
    coinToss = rand() % 2;

    if (coinToss > 0)
      merchantInv.addItem(Weapon(character.getLevel() + rand() % 5, rand() % 4));
    else
      merchantInv.addItem(Armor(character.getLevel() + rand() % 5, rand() % 4));
  }

  while (shopping)
  {
    system("clear");

    std::cout << "= SHOP MENU ="
              << "\n\n";

    std::cout << "0: Leave"
              << "\n";
    std::cout << "1: Buy"
              << "\n";
    std::cout << "2: Sell"
              << "\n";
    std::cout << "\n";

    std::cout << "Choice: ";

    std::cin >> choice;

    while (std::cin.fail() || choice > 3 || choice < 0)
    {
      system("clear");

      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "= SHOP MENU ="
                << "\n\n";

      std::cout << "0: Leave"
                << "\n";
      std::cout << "1: Buy"
                << "\n";
      std::cout << "2: Sell"
                << "\n";

      std::cout << "\n";

      std::cout << "Choice: ";
      std::cin >> choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    // Shop
    switch (choice)
    {
      case 0:  // Leave
        shopping = false;
        break;

      case 1:  // Buy

        std::cout << "= BUY MENU ="
                  << "\n\n";

        std::cout << " - Gold: " << character.getGold() << "\n\n";

        printShop(merchantInv);

        std::cout << "Gold: " << character.getGold() << "\n";
        std::cout << "Choice of item (-1 to cancel): ";
        std::cin >> choice;

        while (std::cin.fail() || choice > merchantInv.size() || choice < -1)
        {
          system("clear");

          std::cout << "Faulty input!"
                    << "\n";
          std::cin.clear();
          std::cin.ignore(100, '\n');

          std::cout << "Gold: " << character.getGold() << "\n";
          std::cout << "Choice of item (-1 to cancel): ";
          std::cin >> choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << "\n";

        if (choice == -1)
        {
          std::cout << "Cancelled..."
                    << "\n";
        }
        else if (character.getGold() >= merchantInv[choice]->getBuyValue())
        {
          character.payGold(merchantInv[choice]->getBuyValue());
          character.addItem(*(merchantInv[choice]));

          std::cout << "Bought item " << merchantInv[choice]->getName() << " -" << merchantInv[choice]->getBuyValue()
                    << "\n";

          merchantInv.removeItem(choice);
        }
        else
        {
          std::cout << "Can't afford this item!"
                    << "\n";
        }

        break;

      case 2:  // Sell

        std::cout << character.getInvAsString(true) << "\n";

        std::cout << "= SELL MENU ="
                  << "\n\n";

        std::cout << " - Gold: " << character.getGold() << "\n\n";

        if (character.getInventorySize() > 0)
        {
          std::cout << "Gold: " << character.getGold() << "\n";
          std::cout << "Choice of item (-1 to cancel): ";

          std::cin >> choice;

          while (std::cin.fail() || choice > character.getInventorySize() || choice < -1)
          {
            system("clear");

            std::cout << "Faulty input!"
                      << "\n";
            std::cin.clear();
            std::cin.ignore(100, '\n');

            std::cout << "Gold: " << character.getGold() << "\n";
            std::cout << "Choice of item (-1 to cancel): ";
            std::cin >> choice;
          }

          std::cin.ignore(100, '\n');
          std::cout << "\n";

          if (choice == -1)
          {
            std::cout << "Cancelled..."
                      << "\n";
          }
          else
          {
            character.gainGold(character.getItem(choice).getSellValue());

            std::cout << "Item sold!"
                      << "\n";
            std::cout << "Gold earned: " << character.getItem(choice).getSellValue() << "\n\n";
            character.removeItem(choice);
          }
        }
        else
        {
          std::cout << "Inventory empty..."
                    << "\n";
        }

        break;

      default:
        break;
    }

    std::cout << "ENTER to continue..."
              << "\n";
    std::cin.get();
  }

  std::cout << "You left the shop.."
            << "\n\n";
}

void Event::enemyEncouter(Character& character, std::vector<Enemy>& enemies)
{
  // Initialize battle
  bool playerTurn = false;
  int choice = 0;

  // Coin toss for turn
  int coinToss = rand() % 2 + 1;

  if (coinToss == 1)
    playerTurn = true;
  else
    playerTurn = false;

  // Enemies
  int nrOfEnemies = rand() % 5 + 1;

  for (size_t i = 0; i < nrOfEnemies; i++)
  {
    enemies.push_back(Enemy(character.getLevel() + rand() % 3));
  }

  // Battle variables
  int damage = 0;
  int gainExp = 0;
  int gainGold = 0;
  int playerTotal = 0;
  int enemyTotal = 0;
  int combatTotal = 0;
  int combatRollPlayer = 0;
  int combatRollEnemy = 0;

  // Battle loop
  while (true)
  {
    if (playerTurn)
    {
      // Menu
      // system("clear");

      std::cout << "= PLAYER TURN ="
                << "\n\n";
      std::cout << "Continue..."
                << "\n\n";
      std::cin.get();
      system("clear");

      std::cout << "= BATTLE MENU ="
                << "\n\n";
      std::cout << "HP: " << character.getHP() << " / " << character.getHPMax() << "\n\n";

      std::cout << "0: Escape"
                << "\n";
      std::cout << "1: Attack"
                << "\n";
      std::cout << "2: Defend"
                << "\n";
      std::cout << "3: Use Item"
                << "\n";
      std::cout << "\n";

      std::cout << "Choice: ";

      std::cin >> choice;

      while (std::cin.fail() || choice > 3 || choice < 0)
      {
        system("clear");

        std::cout << "Faulty input!"
                  << "\n";
        std::cin.clear();
        std::cin.ignore(100, '\n');

        std::cout << "= BATTLE MENU ="
                  << "\n\n";

        std::cout << "0: Escape"
                  << "\n";
        std::cout << "1: Attack"
                  << "\n";
        std::cout << "2: Defend"
                  << "\n";
        std::cout << "3: Use Item"
                  << "\n";
        std::cout << "\n";

        std::cout << "Choice: ";
        std::cin >> choice;
      }

      std::cin.ignore(100, '\n');
      std::cout << "\n";

      // Moves
      switch (choice)
      {
        case 0:  // ESCAPE
          return;
          break;

        case 1:  // ATTACK

          // Select enemy
          std::cout << "Select enemy: "
                    << "\n\n";

          for (size_t i = 0; i < enemies.size(); i++)
          {
            std::cout << i << ": "
                      << "Level: " << enemies[i].getLevel() << " - "
                      << "HP: " << enemies[i].getHp() << "/" << enemies[i].getHpMax() << " - "
                      << "Defense: " << enemies[i].getDefense() << " - "
                      << "Accuracy: " << enemies[i].getAccuracy() << " - "
                      << "Damage: " << enemies[i].getDamageMin() << " - " << enemies[i].getDamageMax() << "\n";
          }

          std::cout << "\n";
          std::cout << "Choice: ";

          std::cin >> choice;

          while (std::cin.fail() || choice >= enemies.size() || choice < 0)
          {
            std::cout << "Faulty input!"
                      << "\n";
            std::cin.clear();
            std::cin.ignore(100, '\n');

            std::cout << "Select enemy: "
                      << "\n\n";
            std::cout << "Choice: ";
            std::cin >> choice;
          }

          std::cin.ignore(100, '\n');
          std::cout << "\n";

          // Attack roll
          // TODO: Use <random> library
          combatTotal = enemies[choice].getDefense() + character.getAccuracy();
          enemyTotal = enemies[choice].getDefense() / (double)combatTotal * 100;
          playerTotal = character.getAccuracy() / (double)combatTotal * 100;
          combatRollPlayer = (playerTotal == 0) ? 0 : rand() % playerTotal;
          combatRollEnemy = (enemyTotal == 0) ? 0 : rand() % enemyTotal;

          std::cout << "Combat total: " << combatTotal << "\n";
          std::cout << "Enemy percent: " << enemyTotal << "\n";
          std::cout << "Player percent: " << playerTotal << "\n\n";
          std::cout << "Player roll: " << combatRollPlayer << "\n";
          std::cout << "Enemy roll: " << combatRollEnemy << "\n\n";

          if (combatRollPlayer > combatRollEnemy)  // Hit
          {
            std::cout << "HIT! "
                      << "\n\n";

            damage = character.getDamage();
            enemies[choice].takeDamage(damage);

            std::cout << "Damage: " << damage << "!"
                      << "\n\n";

            if (!enemies[choice].isAlive())
            {
              std::cout << "ENEMY DEFEATED!"
                        << "\n\n";
              gainExp = enemies[choice].getExp();
              character.gainExp(gainExp);
              gainGold = rand() % enemies[choice].getLevel() * 10 + 1;
              character.gainGold(gainGold);
              std::cout << "EXP GAINED: " << gainExp << "\n";
              std::cout << "GOLD GAINED: " << gainGold << "\n\n";

              // Item roll
              int roll = rand() % 100 + 1;
              int rarity = -1;

              if (roll > 20)
              {
                rarity = 0;  // Common

                roll = rand() % 100 + 1;
                if (roll > 30)
                {
                  rarity = 1;  // Uncommon

                  roll = rand() % 100 + 1;
                  if (roll > 50)
                  {
                    rarity = 2;  // Rare

                    roll = rand() % 100 + 1;
                    if (roll > 70)
                    {
                      rarity = 3;  // Legendary

                      roll = rand() % 100 + 1;
                      if (roll > 90)
                      {
                        rarity = 4;  // Mythic
                      }
                    }
                  }
                }
              }

              if (roll >= 0)
              {
                roll = rand() % 100 + 1;

                if (roll > 50)
                {
                  Weapon tempW(character.getLevel(), rarity);
                  character.addItem(tempW);
                  std::cout << "WEAPON DROP!"
                            << "\n";
                }
                else
                {
                  Armor tempA(character.getLevel(), rarity);
                  character.addItem(tempA);
                  std::cout << "ARMOR DROP!"
                            << "\n";
                }
              }

              enemies.erase(enemies.begin() + choice);
            }
          }
          else  // Miss
          {
            std::cout << "MISSED! \n\n";
          }

          break;

        case 2:  // DEFEND

          break;

        case 3:  // ITEM

          break;

        default:
          break;
      }

      // End turn
      playerTurn = false;
    }
    else if (!playerTurn)
    {
      std::cout << "= ENEMY TURN ="
                << "\n";

      std::cout << "Continue..."
                << "\n\n";
      std::cin.get();
      system("clear");

      // Enemy attack
      for (size_t i = 0; i < enemies.size(); i++)
      {
        std::cout << "Continue..."
                  << "\n\n";
        std::cin.get();
        system("clear");

        std::cout << "Enemy: " << i << "\n\n";

        // Attack roll
        combatTotal = enemies[i].getAccuracy() + (character.getDefense() + character.getAddedDefense());
        enemyTotal = enemies[i].getAccuracy() / (double)combatTotal * 100;
        playerTotal = (character.getDefense() + character.getAddedDefense()) / (double)combatTotal * 100;
        combatRollPlayer = (playerTotal == 0) ? 0 : rand() % playerTotal;
        combatRollEnemy = (enemyTotal == 0) ? 0 : rand() % enemyTotal;

        std::cout << "Combat total: " << combatTotal << "\n";
        std::cout << "Enemy percent: " << enemyTotal << "\n";
        std::cout << "Player percent: " << playerTotal << "\n\n";
        std::cout << "Player roll: " << combatRollPlayer << "\n";
        std::cout << "Enemy roll: " << combatRollEnemy << "\n\n";

        if (combatRollPlayer < combatRollEnemy)  // Hit
        {
          std::cout << "HIT! "
                    << "\n\n";

          damage = enemies[i].getDamage();
          character.takeDamage(damage);

          std::cout << "Damage: " << damage << "!"
                    << "\n";
          std::cout << "HP: " << character.getHP() << " / " << character.getHPMax() << "\n\n";

          if (!character.isAlive())
          {
            std::cout << "YOU ARE DEFEATED!"
                      << "\n\n";
            return;
          }
        }
        else  // Miss
        {
          std::cout << "MISSED! \n\n";
        }
      }

      // End turn
      playerTurn = true;
    }

    // Conditions
    if (!character.isAlive())
    {
      return;
    }
    else if (enemies.size() <= 0)
    {
      return;
    }
  }
}

void Event::puzzleEncouter(Character& character)
{
  bool completed = false;
  int userAns = 0;
  int chances = 2;
  int gainExp = (chances * character.getLevel() * (rand() % 10 + 1));
  int gainGold = (chances * character.getLevel() * (rand() % 10 + 1));

  GPTPuzzle puzzle("/tmp/unique_set.txt");

  while (!completed && chances > 0)
  {
    std::cout << "Chances: " << chances << "\n\n";
    chances--;
    std::cout << puzzle.getAsString() << "\n";

    std::cout << "\nYour ANSWER: ";
    std::cin >> userAns;

    while (std::cin.fail())
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "\nYour ANSWER: ";
      std::cin >> userAns;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    if (puzzle.getCorrectAns() == userAns)
    {
      completed = true;
      character.gainExp(gainExp);
      character.gainGold(gainGold);
      std::cout << "YOU GAINED " << gainExp << " EXP!"
                << "\n";
      std::cout << "YOU GAINED " << gainGold << " GOLD!"
                << "\n\n";
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

void Event::bossEncouter(Character& character, Boss& boss)
{
  // bool playerTurn = false;
  // int choice = 0;

  ////Coin toss for turn
  // int coinToss = rand() % 2 + 1;

  // if (coinToss == 1)
  //	playerTurn = true;
  // else
  //	playerTurn = false;

  ////End conditions
  // bool escape = false;
  // bool playerDefeated = false;
  // bool enemiesDefeated = false;

  ////Enemies
  // int nrOfEnemies = rand() % 5 + 1;

  // for (size_t i = 0; i < nrOfEnemies; i++)
  //{
  //	enemies.push(Enemy(character.getLevel() + rand() % 3));
  // }

  ////Battle variables
  // int damage = 0;
  // int gainExp = 0;
  // int gainGold = 0;
  // int playerTotal = 0;
  // int enemyTotal = 0;
  // int combatTotal = 0;
  // int combatRollPlayer = 0;
  // int combatRollEnemy = 0;

  // while (!escape && !playerDefeated && !enemiesDefeated)
  //{
  //	if (playerTurn && !playerDefeated)
  //	{
  //		//Menu
  //		//system("clear");

  //		std::cout << "= PLAYER TURN =" << "\n\n";
  //		std::cout << "Continue..." << "\n\n";
  //		std::cin.get();
  //		system("clear");

  //		std::cout << "= BATTLE MENU =" << "\n\n";
  //		std::cout << "HP: " << character.getHP() << " / " <<
  // character.getHPMax()
  //<< "\n\n";

  //		std::cout << "0: Escape" << "\n";
  //		std::cout << "1: Attack" << "\n";
  //		std::cout << "2: Defend" << "\n";
  //		std::cout << "3: Use Item" << "\n";
  //		std::cout << "\n";

  //		std::cout << "Choice: ";

  //		std::cin >> choice;

  //		while (std::cin.fail() || choice > 3 || choice < 0)
  //		{
  //			system("clear");

  //			std::cout << "Faulty input!" << "\n";
  //			std::cin.clear();
  //			std::cin.ignore(100, '\n');

  //			std::cout << "= BATTLE MENU =" << "\n\n";

  //			std::cout << "0: Escape" << "\n";
  //			std::cout << "1: Attack" << "\n";
  //			std::cout << "2: Defend" << "\n";
  //			std::cout << "3: Use Item" << "\n";
  //			std::cout << "\n";

  //			std::cout << "Choice: ";
  //			std::cin >> choice;
  //		}

  //		std::cin.ignore(100, '\n');
  //		std::cout << "\n";

  //		//Moves
  //		switch (choice)
  //		{
  //		case 0: //ESCAPE
  //			escape = true;
  //			break;

  //		case 1: //ATTACK

  //				//Select enemy
  //			std::cout << "Select enemy: " << "\n\n";

  //			for (size_t i = 0; i < enemies.size(); i++)
  //			{
  //				std::cout << i << ": "
  //					<< "Level: " << enemies[i].getLevel() <<
  //" -
  //"
  //<< 					"HP: " << enemies[i].getHp() << "/" <<
  // enemies[i].getHpMax() << " - " <<
  // "Defense: " << enemies[i].getDefense() << " - "
  //<< 					"Accuracy: " << enemies[i].getAccuracy()
  //<< " - " << "Damage: " << enemies[i].getDamageMin() << " - " <<
  // enemies[i].getDamageMax() <<
  //					"\n";
  //			}

  //			std::cout << "\n";
  //			std::cout << "Choice: ";

  //			std::cin >> choice;

  //			while (std::cin.fail() || choice >= enemies.size() || choice
  //< 0)
  //			{
  //				std::cout << "Faulty input!" << "\n";
  //				std::cin.clear();
  //				std::cin.ignore(100, '\n');

  //				std::cout << "Select enemy: " << "\n\n";
  //				std::cout << "Choice: ";
  //				std::cin >> choice;
  //			}

  //			std::cin.ignore(100, '\n');
  //			std::cout << "\n";

  //			//Attack roll
  //			combatTotal = enemies[choice].getDefense() +
  // character.getAccuracy(); 			enemyTotal =
  // enemies[choice].getDefense()
  // /
  //(double)combatTotal * 100; 			playerTotal =
  // character.getAccuracy()
  ///
  //(double)combatTotal * 100; 			combatRollPlayer = rand() %
  // playerTotal + 1; 			combatRollEnemy = rand() % enemyTotal +
  // 1;

  //			std::cout << "Combat total: " << combatTotal << "\n";
  //			std::cout << "Enemy percent: " << enemyTotal << "\n";
  //			std::cout << "Player percent: " << playerTotal << "\n\n";
  //			std::cout << "Player roll: " << combatRollPlayer << "\n";
  //			std::cout << "Enemy roll: " << combatRollEnemy << "\n\n";

  //			if (combatRollPlayer > combatRollEnemy) //Hit
  //			{
  //				std::cout << "HIT! " << "\n\n";

  //				damage = character.getDamage();
  //				enemies[choice].takeDamage(damage);

  //				std::cout << "Damage: " << damage << "!" << "\n\n";

  //				if (!enemies[choice].isAlive())
  //				{
  //					std::cout << "ENEMY DEFEATED!" << "\n\n";
  //					gainExp = enemies[choice].getExp();
  //					character.gainExp(gainExp);
  //					gainGold = rand() %
  // enemies[choice].getLevel() * 10
  //+
  // 1; 					character.gainGold(gainGold);
  // std::cout << "EXP GAINED: " << gainExp << "\n";
  // std::cout << "GOLD GAINED: " << gainGold <<
  //"\n\n";

  //					//Item roll
  //					int roll = rand() % 100 + 1;
  //					int rarity = -1;

  //					if (roll > 20)
  //					{
  //						rarity = 0; //Common

  //						roll = rand() % 100 + 1;
  //						if (roll > 30)
  //						{
  //							rarity = 1; //Uncommon

  //							roll = rand() % 100 + 1;
  //							if (roll > 50)
  //							{
  //								rarity = 2;
  ////Rare

  //								roll = rand() %
  // 100
  //+
  // 1; 								if (roll
  // > 70)
  //								{
  //									rarity =
  // 3;
  ////Legendary

  //									roll =
  // rand() % 100
  //+
  // 1; if (roll > 90)
  //									{
  //										rarity
  //= 4;
  ////Mythic
  //									}
  //								}
  //							}
  //						}
  //					}

  //					if (roll >= 0)
  //					{
  //						roll = rand() % 100 + 1;

  //						if (roll > 50)
  //						{
  //							Weapon
  // tempW(character.getLevel(), rarity);
  // character.addItem(tempW);
  // std::cout << "WEAPON DROP!" <<
  // "\n";
  //						}
  //						else
  //						{
  //							Armor
  // tempA(character.getLevel(), rarity);
  // character.addItem(tempA);
  // std::cout << "ARMOR DROP!" <<
  // "\n";
  //						}
  //					}

  //					enemies.remove(choice);
  //				}
  //			}
  //			else //Miss
  //			{
  //				std::cout << "MISSED! \n\n";
  //			}

  //			break;

  //		case 2: //DEFEND

  //			break;

  //		case 3: //ITEM

  //			break;

  //		default:
  //			break;
  //		}

  //		//End turn
  //		playerTurn = false;
  //	}
  //	else if (!playerTurn && !playerDefeated && !escape && !enemiesDefeated)
  //	{
  //		std::cout << "= ENEMY TURN =" << "\n";

  //		std::cout << "Continue..." << "\n\n";
  //		std::cin.get();
  //		system("clear");

  //		//Enemy attack
  //		for (size_t i = 0; i < enemies.size(); i++)
  //		{
  //			std::cout << "Continue..." << "\n\n";
  //			std::cin.get();
  //			system("clear");

  //			std::cout << "Enemy: " << i << "\n\n";

  //			//Attack roll
  //			combatTotal = enemies[i].getAccuracy() +
  //(character.getDefense()
  //+ character.getAddedDefense()); 			enemyTotal =
  // enemies[i].getAccuracy() /
  //(double)combatTotal * 100; 			playerTotal =
  //(character.getDefense()
  //+ character.getAddedDefense()) / (double)combatTotal * 100;
  // combatRollPlayer = rand() % playerTotal + 1;
  // combatRollEnemy = rand() % enemyTotal + 1;

  //			std::cout << "Combat total: " << combatTotal << "\n";
  //			std::cout << "Enemy percent: " << enemyTotal << "\n";
  //			std::cout << "Player percent: " << playerTotal << "\n\n";
  //			std::cout << "Player roll: " << combatRollPlayer << "\n";
  //			std::cout << "Enemy roll: " << combatRollEnemy << "\n\n";

  //			if (combatRollPlayer < combatRollEnemy) //Hit
  //			{
  //				std::cout << "HIT! " << "\n\n";

  //				damage = enemies[i].getDamage();
  //				character.takeDamage(damage);

  //				std::cout << "Damage: " << damage << "!" << "\n";
  //				std::cout << "HP: " << character.getHP() << " / " <<
  // character.getHPMax() << "\n\n";

  //				if (!character.isAlive())
  //				{
  //					std::cout << "YOU ARE DEFEATED!" << "\n\n";
  //					playerDefeated = true;
  //				}
  //			}
  //			else //Miss
  //			{
  //				std::cout << "MISSED! \n\n";
  //			}
  //		}

  //		//End turn
  //		playerTurn = true;
  //	}

  //	//Conditions
  //	if (!character.isAlive())
  //	{
  //		playerDefeated = true;
  //	}
  //	else if (enemies.size() <= 0)
  //	{
  //		enemiesDefeated = true;
  //	}
  //}
}
