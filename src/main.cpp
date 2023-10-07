#include "Game.h"
// TRY GPT
#include "ChatGPT/include/ChatGPT.h"
#include "ChatGPT/include/Error.h"
#include <cstdlib>

int main()
{
  auto console = spdlog::stdout_color_mt("console");
  spdlog::set_level(spdlog::level::debug);  // Set global log level to debug

#ifdef NDEBUG
  spdlog::info("Release build");
#else
  spdlog::info("Debug build");
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