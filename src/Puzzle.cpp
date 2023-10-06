#include "Puzzle.h"

Puzzle::Puzzle(std::string file_name)
{
  // SAVE/LOAD FORMAT
  /*
  Question
  nrOfAns
  answers
  correctAns
  */

  correct_answer_ = 0;
  std::ifstream inFile(file_name);

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

std::string Puzzle::getAsString()
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
