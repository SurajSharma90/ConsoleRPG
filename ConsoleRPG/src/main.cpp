#include "Game.h"

int main()
{
#ifdef NDEBUG
  std::cout << "Release build" << std::endl;
#else
  std::cout << "Debug build" << std::endl;
#endif

  srand(time(NULL));

  Game game;
  game.initGame();

  while (game.getPlaying())
  {
    game.mainMenu();
  }

  return 0;
}