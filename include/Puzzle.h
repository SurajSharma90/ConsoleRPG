#pragma once

#include "STLINCLUDE.h"
#include "ChatGPT/include/ChatGPT.h"
#include "ChatGPT/include/Error.h"
#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>  // for std::shuffle
#include <random>     // for std::default_random_engine
#include <set>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Puzzle
{
private:
  std::string question_;
  std::vector<std::string> answers_;
  int correct_answer_;

public:
  Puzzle(std::string file_name);
  virtual ~Puzzle();
  std::string getAsString() const;

  const int getCorrectAns() const
  {
    return correct_answer_;
  }
};

// TODO: Make unique_string persistent (it should be recorded somewhere)
class GPTPuzzle
{
private:
  std::string question_;
  std::vector<std::string> answers_;
  int correct_answer_index_;
  std::set<std::string>& unique_strings_;

  /**
   * @brief inserts string in a set if possible
   *
   * @param str
   * @param unique_strings
   * @return true - insert succeeded
   * @return false - value already existed in the set
   */
  bool insertIfNotExists(const std::string& str, std::set<std::string>& unique_strings);

  /**
   * @brief Check if the choice is correct
   *
   * @param choice
   * @return true
   * @return false
   */
  bool is_correct(int choice) const;

public:
  /**
   * @brief Construct a new GPTPuzzle object
   *
   * @param unique_strings - set answers that have already been used
   */
  GPTPuzzle(std::set<std::string>& unique_strings);

  // Display the puzzle
  std::string getAsString() const;

  const int getCorrectAns() const;

  static void example(std::set<std::string>& unique_string)
  {
    GPTPuzzle gpt_puzzle(unique_string);

    spdlog::info(gpt_puzzle.getAsString());

    int attempts = 2;
    int userChoice;

    while (attempts > 0)
    {
      std::cout << "Enter your choice (1-3): ";
      std::cin >> userChoice;

      if (gpt_puzzle.is_correct(userChoice))
      {
        std::cout << "Correct!" << std::endl;
        break;
      }
      else
      {
        --attempts;
        if (attempts > 0)
        {
          std::cout << "Wrong answer. You have " << attempts << " attempt(s) left." << std::endl;
        }
        else
        {
          std::cout << "Sorry, you're out of attempts." << std::endl;
        }
      }
    }

    return;
  }
};
