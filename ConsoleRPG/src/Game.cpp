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

// Functions
void Game::initGame()
{
  std::ifstream in;
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
  std::cout << "ENTER to continue..."
            << "\n";
  std::cin.get();
  system("clear");

  if (this->characters[activeCharacter].isAlive())
  {
    if (this->characters[activeCharacter].getExp() >= this->characters[activeCharacter].getExpNext())
    {
      std::cout << "LEVEL UP AVAILABLE! \n\n";
    }

    std::cout << "= MAIN MENU ="
              << "\n"
              << "\n";

    std::cout << "= Active character: " << this->characters[activeCharacter].getName()
              << " Nr: " << this->activeCharacter + 1 << "/" << this->characters.size() << " ="
              << "\n"
              << "\n";

    std::cout << "0: Quit"
              << "\n";
    std::cout << "1: Travel"
              << "\n";
    std::cout << "2: Level up"
              << "\n";
    std::cout << "3: Rest"
              << "\n";
    std::cout << "4: Character sheet"
              << "\n";
    std::cout << "5: Create new character"
              << "\n";
    std::cout << "6: Select character"
              << "\n";
    std::cout << "7: Save characters"
              << "\n";
    std::cout << "8: Load characters"
              << "\n";

    std::cout << "\n";

    std::cout << "\n"
              << "Choice: ";
    std::cin >> this->choice;

    while (std::cin.fail() || this->choice > 9)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "\n"
                << "Choice (0 - 8): ";
      std::cin >> this->choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    switch (this->choice)
    {
      case 0:  // QUIT
        playing = false;
        this->saveCharacters();

        break;

      case 1:  // TRAVEL
        travel();

        break;

      case 2:  // LEVEL UP
        this->levelUpCharacter();

        break;

      case 3:  // REST
        rest();

        break;

      case 4:  // CHAR SHEET
        this->characterMenu();
        break;

      case 5:  // CREATE NEW CHAR
        createNewCharacter();
        saveCharacters();
        break;

      case 6:  // SELECT CHAR
        selectCharacter();
        break;

      case 7:  // SAVE CHARS
        saveCharacters();
        break;

      case 8:  // LOAD CHARS
        loadCharacters();
        break;

      default:
        break;
    }
  }
  else
  {
    std::cout << "= YOU ARE DEAD, LOAD? ="
              << "\n"
              << "\n";
    std::cout << "(0) Yes, (1) No "
              << "\n";
    std::cin >> this->choice;

    while (std::cin.fail() || this->choice < 0 || this->choice > 1)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "(0) Yes, (1) No "
                << "\n";
      std::cin >> this->choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    if (this->choice == 0)
      this->loadCharacters();
    else
      playing = false;
  }
}

void Game::createNewCharacter()
{
  std::string name = "";
  std::cout << "Character name: ";
  std::getline(std::cin, name);

  for (size_t i = 0; i < this->characters.size(); i++)
  {
    while (name == this->characters[i].getName())
    {
      std::cout << "Error! Character already exists!"
                << "\n";
      std::cout << "Character name: ";
      std::getline(std::cin, name);
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
    std::cout << "You have statpoints to allocate!"
              << "\n\n";

    std::cout << "Stat to upgrade: "
              << "\n";
    std::cout << "0: Strength "
              << "\n";
    std::cout << "1: Vitality "
              << "\n";
    std::cout << "2: Dexterity "
              << "\n";
    std::cout << "3: Intelligence "
              << "\n";

    std::cin >> this->choice;

    while (std::cin.fail() || this->choice > 3)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "Stat to upgrade: "
                << "\n";
      std::cin >> this->choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    switch (this->choice)
    {
      case 0:  // STRENGTH
        this->characters[activeCharacter].addToStat(0, 1);
        break;

      case 1:  // VITALITY
        this->characters[activeCharacter].addToStat(1, 1);
        break;

      case 2:  // DEXTERITY
        this->characters[activeCharacter].addToStat(2, 1);
        break;

      case 3:  // INTELLIGENCE
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
    system("clear");
    std::cout << gui::menu_title("CHARACTER MENU");

    std::cout << gui::menu_divider();

    characters[activeCharacter].printStats();

    std::cout << gui::menu_divider();

    std::cout << "= MENU ="
              << "\n";
    std::cout << gui::menu_item(0, "Back");
    std::cout << gui::menu_item(1, "Print Inventory");
    std::cout << gui::menu_item(2, "Equip Item");
    std::cout << "\n";
    std::cout << "Choice: ";

    std::cin >> this->choice;

    while (std::cin.fail() || this->choice < 0 || this->choice > 2)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "= MENU ="
                << "\n";
      std::cout << "0: Back"
                << "\n";
      std::cout << "1: Print Inventory"
                << "\n";
      std::cout << "2: Equip Item"
                << "\n";
      std::cout << "\n";
      std::cout << "Choice: ";
      std::cin >> this->choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    switch (this->choice)
    {
      case 1:
        std::cout << this->characters[this->activeCharacter].getInvAsString();

        break;

      case 2:
        // TODO: After equipping item, it returns to main menu instead of returning for the inventory
        std::cout << this->characters[this->activeCharacter].getInvAsString();

        std::cout << "Item index: ";
        std::cin >> this->choice;

        while (std::cin.fail() || this->choice < 0 ||
               this->choice >= this->characters[this->activeCharacter].getInventorySize())
        {
          std::cout << "Faulty input!"
                    << "\n";
          std::cin.clear();
          std::cin.ignore(100, '\n');

          std::cout << "Item index: ";
          std::cin >> this->choice;
        }

        std::cin.ignore(100, '\n');
        std::cout << "\n";

        this->characters[this->activeCharacter].equipItem(this->choice);

        break;
      default:
        break;
    }

    if (this->choice > 0)
    {
      std::cout << "ENTER to continue..."
                << "\n";
      std::cin.get();
    }

  } while (this->choice > 0);
}

void Game::saveCharacters()
{
  std::ofstream outFile(fileName);

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
  std::ifstream inFile(fileName);

  this->characters.clear();

  std::string name = "";
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

  // Item
  int itemType = 0;
  int defense = 0;
  int type = 0;
  int damageMin = 0;
  int damageMax = 0;
  // name
  // level
  int buyValue = 0;
  int sellValue = 0;
  int rarity = 0;

  Inventory tempItems;

  std::string line = "";
  std::stringstream str;

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

      // Create characyer
      Character temp(name, distanceTravelled, gold, level, exp, strength, vitality, dexterity, intelligence, hp,
                     stamina, statPoints);

      // Weapon
      str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> damageMin >> damageMax;

      Weapon weapon(damageMin, damageMax, name, level, buyValue, sellValue, rarity);

      // Armor head
      str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> defense >> type;

      Armor armor_head(type, defense, name, level, buyValue, sellValue, rarity);

      // Armor chest
      str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> defense >> type;

      Armor armor_chest(type, defense, name, level, buyValue, sellValue, rarity);

      // Armor arms
      str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> defense >> type;

      Armor armor_arms(type, defense, name, level, buyValue, sellValue, rarity);

      // Armor legs
      str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> defense >> type;

      Armor armor_legs(type, defense, name, level, buyValue, sellValue, rarity);

      temp.setWeapon(weapon);
      temp.setArmorHead(armor_head);
      temp.setArmorChest(armor_chest);
      temp.setArmorArms(armor_arms);
      temp.setArmorLegs(armor_legs);

      // Add Inventory Items
      str.clear();
      line.clear();
      getline(inFile, line);

      str.str(line);

      while (str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> damageMin >> damageMax)
      {
        temp.addItem(Weapon(damageMin, damageMax, name, level, buyValue, sellValue, rarity));
      }

      str.clear();
      line.clear();
      getline(inFile, line);

      str.str(line);

      while (str >> itemType >> name >> level >> rarity >> buyValue >> sellValue >> defense >> type)
      {
        temp.addItem(Armor(type, defense, name, level, buyValue, sellValue, rarity));
      }

      std::cout << "Character " << temp.getName() << " loaded!\n";

      characters.push_back(std::move(temp));
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
  std::cout << "Select character: "
            << "\n\n";

  for (size_t i = 0; i < this->characters.size(); i++)
  {
    std::cout << "Index: " << i << " = " << this->characters[i].getName()
              << " Level: " << this->characters[i].getLevel() << "\n";
  }

  std::cout << "\n";

  std::cout << "Choice: ";

  std::cin >> this->choice;

  while (std::cin.fail() || this->choice >= this->characters.size() || this->choice < 0)
  {
    std::cout << "Faulty input!"
              << "\n";
    std::cin.clear();
    std::cin.ignore(100, '\n');

    std::cout << "Select character: "
              << "\n";
    std::cin >> this->choice;
  }

  std::cin.ignore(100, '\n');
  std::cout << "\n";

  this->activeCharacter = this->choice;

  std::cout << this->characters[this->activeCharacter].getName() << " is SELECTED!"
            << "\n\n";
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
  std::cout << "= REST ="
            << "\n\n";
  std::cout << "Resting costs you: " << restCost << "\n";
  std::cout << "Your gold: " << this->characters[this->activeCharacter].getGold() << "\n";
  std::cout << "HP: " << this->characters[this->activeCharacter].getHP() << " / "
            << this->characters[this->activeCharacter].getHPMax() << "\n\n";

  if (this->characters[this->activeCharacter].getGold() < restCost)
  {
    std::cout << "NOT ENOUGH MONEY, SORRY BUDDY!"
              << "\n\n";
  }
  else if (this->characters[this->activeCharacter].getHP() >= this->characters[this->activeCharacter].getHPMax())
  {
    std::cout << "ALREADY AT FULL HEALTH BUDDY!"
              << "\n\n";
  }
  else
  {
    std::cout << "\n\n Rest? (0) Yes, (1) No..."
              << "\n\n";

    std::cin >> this->choice;

    while (std::cin.fail() || this->choice < 0 || this->choice > 1)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "\n\n Rest? (0) Yes, (1) No..."
                << "\n\n";
      std::cin >> this->choice;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    if (this->choice == 0)
    {
      this->characters[this->activeCharacter].resetHP();
      this->characters[this->activeCharacter].payGold(restCost);
      std::cout << "RESTED!"
                << "\n\n";
    }
    else
    {
      std::cout << "MAYBE NEXT TIME!"
                << "\n\n";
    }
  }
}