#pragma once
#include "STLINCLUDE.h"

#include "Event.h"

class Game
{
private:
  int choice_;
  bool playing_;

  // Character related
  int active_character_;
  std::vector<Character> characters_;
  std::string fileName_;

  // Enemies
  std::vector<Enemy> enemies_;

public:
  Game();
  virtual ~Game();

  // Operators

  // Functions
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

  // Accessors
  inline bool getPlaying() const
  {
    return playing_;
  }

  // Modifiers
};
