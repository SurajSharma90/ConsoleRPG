#include "Game.h"

Game::Game()
{
  choice_ = 0;
  playing_ = true;
  active_character_ = 0;
  fileName_ = "characters_.txt";
}

Game::~Game()
{
}

// Functions
void Game::initGame()
{
  std::ifstream in;
  in.open("characters_.txt");

  Weapon::initNames();
  Armor::initNames();

  if (in.is_open())
    loadCharacters();
  else
  {
    createNewCharacter();
    saveCharacters();
  }

  in.close();
}

void Game::mainMenu()
{
  std::cout << "ENTER to continue..."
            << "\n";
  std::cin.get();
  system("clear");

  if (characters_[active_character_].isAlive())
  {
    if (characters_[active_character_].getExp() >= characters_[active_character_].getExpNext())
    {
      std::cout << "LEVEL UP AVAILABLE! \n\n";
    }

    std::cout << "= MAIN MENU ="
              << "\n"
              << "\n";

    std::cout << "= Active character: " << characters_[active_character_].getName() << " Nr: " << active_character_ + 1
              << "/" << characters_.size() << " ="
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
    std::cin >> choice_;

    while (std::cin.fail() || choice_ > 9)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "\n"
                << "Choice (0 - 8): ";
      std::cin >> choice_;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    switch (choice_)
    {
      case 0:  // QUIT
        playing_ = false;
        saveCharacters();

        break;

      case 1:  // TRAVEL
        travel();

        break;

      case 2:  // LEVEL UP
        levelUpCharacter();

        break;

      case 3:  // REST
        rest();

        break;

      case 4:  // CHAR SHEET
        characterMenu();
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
    std::cin >> choice_;

    while (std::cin.fail() || choice_ < 0 || choice_ > 1)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "(0) Yes, (1) No "
                << "\n";
      std::cin >> choice_;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    if (choice_ == 0)
      loadCharacters();
    else
      playing_ = false;
  }
}

void Game::createNewCharacter()
{
  std::string name = "";
  std::cout << "Character name: ";
  std::getline(std::cin, name);

  for (size_t i = 0; i < characters_.size(); i++)
  {
    while (name == characters_[i].getName())
    {
      std::cout << "Error! Character already exists!"
                << "\n";
      std::cout << "Character name: ";
      std::getline(std::cin, name);
    }
  }

  characters_.push_back(Character());
  active_character_ = characters_.size() - 1;
  characters_[active_character_].initialize(name);
}

void Game::levelUpCharacter()
{
  characters_[active_character_].levelUp();

  if (characters_[active_character_].getStatPoints() > 0)
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

    std::cin >> choice_;

    while (std::cin.fail() || choice_ > 3)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "Stat to upgrade: "
                << "\n";
      std::cin >> choice_;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    switch (choice_)
    {
      case 0:  // STRENGTH
        characters_[active_character_].addToStat(0, 1);
        break;

      case 1:  // VITALITY
        characters_[active_character_].addToStat(1, 1);
        break;

      case 2:  // DEXTERITY
        characters_[active_character_].addToStat(2, 1);
        break;

      case 3:  // INTELLIGENCE
        characters_[active_character_].addToStat(3, 1);
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

    characters_[active_character_].printStats();

    std::cout << gui::menu_divider();

    std::cout << "= MENU ="
              << "\n";
    std::cout << gui::menu_item(0, "Back");
    std::cout << gui::menu_item(1, "Print Inventory");
    std::cout << gui::menu_item(2, "Equip Item");
    std::cout << "\n";
    std::cout << "Choice: ";

    std::cin >> choice_;

    while (std::cin.fail() || choice_ < 0 || choice_ > 2)
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
      std::cin >> choice_;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    switch (choice_)
    {
      case 1:
        std::cout << characters_[active_character_].getInvAsString();

        break;

      case 2:
        // TODO: After equipping item, it returns to main menu instead of returning for the inventory
        std::cout << characters_[active_character_].getInvAsString();

        std::cout << "Item index: ";
        std::cin >> choice_;

        while (std::cin.fail() || choice_ < 0 || choice_ >= characters_[active_character_].getInventorySize())
        {
          std::cout << "Faulty input!"
                    << "\n";
          std::cin.clear();
          std::cin.ignore(100, '\n');

          std::cout << "Item index: ";
          std::cin >> choice_;
        }

        std::cin.ignore(100, '\n');
        std::cout << "\n";

        characters_[active_character_].equipItem(choice_);

        break;
      default:
        break;
    }

    if (choice_ > 0)
    {
      std::cout << "ENTER to continue..."
                << "\n";
      std::cin.get();
    }

  } while (choice_ > 0);
}

void Game::saveCharacters()
{
  std::ofstream outFile(fileName_);

  if (outFile.is_open())
  {
    for (size_t i = 0; i < characters_.size(); i++)
    {
      outFile << characters_[i].getAsString() << "\n";
      outFile << characters_[i].getInvAsStringSave() << "\n";
    }
  }

  outFile.close();
}

void Game::loadCharacters()
{
  std::ifstream inFile(fileName_);

  characters_.clear();

  std::string name = "";
  int distance_traveled = 0;
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
      str >> distance_traveled;
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
      Character temp(name, distance_traveled, gold, level, exp, strength, vitality, dexterity, intelligence, hp,
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

      characters_.push_back(std::move(temp));
      str.clear();
    }
  }

  inFile.close();

  if (characters_.size() <= 0)
  {
    throw "ERROR! NO CHARACTERS LOADED OR EMPTY FILE!";
  }
}

void Game::selectCharacter()
{
  std::cout << "Select character: "
            << "\n\n";

  for (size_t i = 0; i < characters_.size(); i++)
  {
    std::cout << "Index: " << i << " = " << characters_[i].getName() << " Level: " << characters_[i].getLevel() << "\n";
  }

  std::cout << "\n";

  std::cout << "Choice: ";

  std::cin >> choice_;

  while (std::cin.fail() || choice_ >= characters_.size() || choice_ < 0)
  {
    std::cout << "Faulty input!"
              << "\n";
    std::cin.clear();
    std::cin.ignore(100, '\n');

    std::cout << "Select character: "
              << "\n";
    std::cin >> choice_;
  }

  std::cin.ignore(100, '\n');
  std::cout << "\n";

  active_character_ = choice_;

  std::cout << characters_[active_character_].getName() << " is SELECTED!"
            << "\n\n";
}

void Game::travel()
{
  characters_[active_character_].travel();

  Event ev;

  ev.generateEvent(characters_[active_character_], enemies_);
}

void Game::rest()
{
  int restCost = characters_[active_character_].getHPMax() - characters_[active_character_].getHP();
  std::cout << "= REST ="
            << "\n\n";
  std::cout << "Resting costs you: " << restCost << "\n";
  std::cout << "Your gold: " << characters_[active_character_].getGold() << "\n";
  std::cout << "HP: " << characters_[active_character_].getHP() << " / " << characters_[active_character_].getHPMax()
            << "\n\n";

  if (characters_[active_character_].getGold() < restCost)
  {
    std::cout << "NOT ENOUGH MONEY, SORRY BUDDY!"
              << "\n\n";
  }
  else if (characters_[active_character_].getHP() >= characters_[active_character_].getHPMax())
  {
    std::cout << "ALREADY AT FULL HEALTH BUDDY!"
              << "\n\n";
  }
  else
  {
    std::cout << "\n\n Rest? (0) Yes, (1) No..."
              << "\n\n";

    std::cin >> choice_;

    while (std::cin.fail() || choice_ < 0 || choice_ > 1)
    {
      std::cout << "Faulty input!"
                << "\n";
      std::cin.clear();
      std::cin.ignore(100, '\n');

      std::cout << "\n\n Rest? (0) Yes, (1) No..."
                << "\n\n";
      std::cin >> choice_;
    }

    std::cin.ignore(100, '\n');
    std::cout << "\n";

    if (choice_ == 0)
    {
      characters_[active_character_].resetHP();
      characters_[active_character_].payGold(restCost);
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