#include "Puzzle.h"

Puzzle::Puzzle(const boost::filesystem::path& filepath)
{
  // SAVE/LOAD FORMAT
  /*
  Question
  nrOfAns
  answers
  correctAns
  */

  correct_answer_ = 0;
  std::ifstream inFile(filepath.string());

  int nrOfAns = 0;
  std::string answer = "";
  int correctAns = 0;

  if (!inFile.is_open())
  {
    throw std::runtime_error("Could not open puzzle!");
  }

  std::getline(inFile, question_);
  inFile >> nrOfAns;
  inFile.ignore();

  for (size_t i = 0; i < nrOfAns; i++)
  {
    std::getline(inFile, answer);
    answers_.push_back(answer);
  }

  inFile >> correctAns;
  correct_answer_ = correctAns;
  inFile.ignore();

  inFile.close();
}

Puzzle::~Puzzle()
{
}

std::string Puzzle::getAsString() const
{
  std::string answers = "";

  for (size_t i = 0; i < answers_.size(); i++)
  {
    answers += std::to_string(i) + ": " + answers_[i] + "\n";
  }

  /*return question_ + "\n" + "\n"
    + answers + "\n"
    + std::to_string(correct_answer_) + "\n";*/

  return question_ + "\n" + "\n" + answers + "\n";
}

GPTPuzzle::GPTPuzzle(const boost::filesystem::path& filepath)
  : filepath_(filepath), unique_strings_(loadSetFromFile(filepath_))
{
  // API token as argument
  const char* apiKey = std::getenv("OPEN_API_KEY");
  if (!apiKey)
  {
    spdlog::critical("Environment variable OPEN_API_KEY is not set.");
    throw std::runtime_error("No environment variable to provide Open API key provided.");
  }
  OpenAI::ChatGPT chatGpt{ apiKey };
  nlohmann::json j;

  std::string correct_answer;
  do
  {
    try
    {
      // type of user and the message to ask
      auto response = chatGpt.askChatGPT(
          "user", "Give me a new logic riddle in the json format: {riddle, wrong_answers: [], correct_answer}.");

      spdlog::debug("Raw response: \n{}", response.choices[0].message.content);
      j = nlohmann::json::parse(response.choices[0].message.content);
      spdlog::debug("JSON parsed: \n{}", j.dump(4));
    }
    catch (OpenAI::Error& e)
    {
      // JSON error returned by the server
      std::cout << e.what();
      continue;
    }
    catch (std::exception& e)
    {
      std::cout << e.what();
      continue;
    }

    correct_answer = j["correct_answer"].get<std::string>();
    question_ = j["riddle"];
    answers_ = j["wrong_answers"].get<std::vector<std::string>>();
    answers_.push_back(correct_answer);
    correct_answer_index_ = answers_.size() - 1;  // The correct answer is initially the last one
  } while (!insertIfNotExists(correct_answer, unique_strings_));
  // Shuffle the answers_
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(answers_.begin(), answers_.end(), g);

  // Update the correct_answer_index_ after shuffling
  for (size_t i = 0; i < answers_.size(); ++i)
  {
    if (answers_[i] == j["correct_answer"].get<std::string>())
    {
      correct_answer_index_ = i;
      break;
    }
  }
}

GPTPuzzle::~GPTPuzzle()
{
  spdlog::debug("Calling destructor");
  saveSetToFile(unique_strings_, filepath_);
}

bool GPTPuzzle::insertIfNotExists(const std::string& str, std::set<std::string>& unique_strings)
{
  spdlog::debug("Checking if {} exists in the set", str);
  auto [_, inserted] = unique_strings.insert(str);

  spdlog::debug("Current set:");
  for (auto& s : unique_strings)
  {
    spdlog::debug(s);
  }

  spdlog::debug("--");
  return inserted;
}

std::string GPTPuzzle::getAsString() const
{
  spdlog::info("Riddle: {}", question_);
  std::stringstream ss;
  ss << "Answers: \n";
  for (size_t i = 0; i < answers_.size(); ++i)
  {
    ss << i + 1 << ". " << answers_[i] << '\n';
  }
  return ss.str();
}

const int GPTPuzzle::getCorrectAns() const
{
  return correct_answer_index_ + 1;
}

// Check if the provided answer is correct
bool GPTPuzzle::is_correct(int choice) const
{
  return choice == correct_answer_index_ + 1;  // +1 because choices are 1-based
}

std::set<std::string> GPTPuzzle::loadSetFromFile(const boost::filesystem::path& filepath)
{
  std::set<std::string> loadedSet;

  if (!boost::filesystem::exists(filepath))
  {
    spdlog::debug("File doesn't exist: {}", filepath.string());
    std::ofstream outFile(filepath.string());  // This will create the file
    if (!outFile.good())
    {
      spdlog::error("Failed to create file: {}", filepath.string());
      return loadedSet;
    }
  }

  std::ifstream file(filepath.string());
  if (!file.good())
  {
    spdlog::error("Failed to open file for reading: {}", filepath.string());
    return loadedSet;
  }

  std::string line;
  while (std::getline(file, line))
  {
    loadedSet.insert(line);
  }

  return loadedSet;
}

void GPTPuzzle::saveSetToFile(const std::set<std::string>& data, const boost::filesystem::path& filepath)
{
  std::ofstream file(filepath.string(), std::ios::out);  // Overwrite the file

  if (!file.is_open())
  {
    spdlog::error("Failed to open file for writing: {}", filepath.string());
    return;
  }

  for (const auto& item : data)
  {
    file << item << '\n';
  }

  file.close();
}