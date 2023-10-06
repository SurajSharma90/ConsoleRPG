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

class Puzzle
{
private:
  std::string question_;
  std::vector<std::string> answers_;
  int correct_answer_;

public:
  Puzzle(std::string file_name);
  virtual ~Puzzle();
  std::string getAsString();

  inline const int& getCorrectAns() const
  {
    return correct_answer_;
  }
};

class GPTPuzzle
{
private:
  std::string riddle;
  std::vector<std::string> options;
  int correct_answer_index;
  std::set<std::string>& unique_strings_;

public:
  // Constructor from JSON
  GPTPuzzle(std::set<std::string>& unique_strings) : unique_strings_(unique_strings)
  {
    std::cout << "Constructor Called" << std::endl;
    // API token as argument
    const char* apiKey = std::getenv("OPEN_API_KEY");
    if (!apiKey)
    {
      std::cout << "Environment variable OPEN_API_KEY is not set." << std::endl;
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
        // TODO: Check if the answer has alrady been used and check if the format is valid (wouldnt cause throw)
        auto response = chatGpt.askChatGPT(
            "user", "Give me a new logic riddle in the json format: {riddle, wrong_answers: [], correct_answer}.");

        std::cout << "Raw response: \n" << response.choices[0].message.content << std::endl;
        j = nlohmann::json::parse(response.choices[0].message.content);
        std::cout << "JSON parsed: \n" << j.dump(4) << std::endl;
      }
      catch (OpenAI::Error& e)
      {
        // JSON error returned by the server
        std::cout << e.what();
      }

      correct_answer = j["correct_answer"].get<std::string>();
      riddle = j["riddle"];
      options = j["wrong_answers"].get<std::vector<std::string>>();
      options.push_back(correct_answer);
      correct_answer_index = options.size() - 1;  // The correct answer is initially the last one
    } while (insertIfNotExists(correct_answer, unique_strings_));
    // Shuffle the options
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(options.begin(), options.end(), g);

    // Update the correct_answer_index after shuffling
    for (size_t i = 0; i < options.size(); ++i)
    {
      if (options[i] == j["correct_answer"].get<std::string>())
      {
        correct_answer_index = i;
        break;
      }
    }
  }

  bool insertIfNotExists(const std::string& str, std::set<std::string>& unique_strings)
  {
    std::cout << "Checking if " << str << " exists in the set";
    auto [_, inserted] = unique_strings.insert(str);
    std::cout << "Current set: ";

    for (auto& s : unique_strings)
    {
      std::cout << s << " | " << std::endl;
    }
    return inserted;
  }

  // Display the puzzle
  void display() const
  {
    std::cout << "Riddle: " << riddle << std::endl;
    std::cout << "Options:" << std::endl;
    for (size_t i = 0; i < options.size(); ++i)
    {
      std::cout << i + 1 << ". " << options[i] << std::endl;
    }
  }

  // Check if the provided answer is correct
  bool is_correct(int choice) const
  {
    return choice == correct_answer_index + 1;  // +1 because choices are 1-based
  }

  static void example(std::set<std::string>& unique_string)
  {
    GPTPuzzle gpt_puzzle(unique_string);

    gpt_puzzle.display();

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
