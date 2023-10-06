#include "Game.h"
// TRY GPT
#include "ChatGPT/include/ChatGPT.h"
#include "ChatGPT/include/Error.h"
#include <cstdlib>

int main()
{
#ifdef NDEBUG
  std::cout << "Release build" << std::endl;
#else
  std::cout << "Debug build" << std::endl;
#endif

  for (int i = 0; i < 5; ++i)
  {
    GPTPuzzle::example();
  }
  srand(time(NULL));

  Game game;
  game.initGame();

  while (game.getPlaying())
  {
    game.mainMenu();
  }

  return 0;
}