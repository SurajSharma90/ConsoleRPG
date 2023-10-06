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

  // API token as argument
  const char* apiKey = std::getenv("OPEN_API_KEY");
  if (!apiKey)
  {
    std::cout << "Environment variable OPEN_API_KEY is not set." << std::endl;
    return 1;
  }
  OpenAI::ChatGPT chatGpt{ apiKey };
  try
  {
    // type of user and the message to ask
    auto response = chatGpt.askChatGPT(
        "user", "Give me a riddle and suggest two wrong answers and one correct, mark the correct one");
    // Iterate all answers
    for (const auto& choice : response.choices)
    {
      std::cout << choice.message.content;
    }
  }
  catch (OpenAI::Error& e)
  {
    // JSON error returned by the server
    std::cout << e.what();
  }
  return 0;
}