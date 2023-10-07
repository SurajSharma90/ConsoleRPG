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

class GPTPuzzle
{
private:
  std::string question_;
  std::vector<std::string> answers_;
  int correct_answer_index_;
  std::set<std::string>& unique_strings_;

  std::string getPreviousAnswers()
  {
    std::stringstream ss;
    for (const auto& v : unique_strings_)
    {
      ss << v << ", ";
    }
    return ss.str();
  }

public:
  // Constructor from JSON
  GPTPuzzle(std::set<std::string>& unique_strings) : unique_strings_(unique_strings)
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

  bool insertIfNotExists(const std::string& str, std::set<std::string>& unique_strings)
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

  // Display the puzzle
  std::string getAsString() const
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

  const int getCorrectAns() const
  {
    return correct_answer_index_ + 1;
  }

  // Check if the provided answer is correct
  bool is_correct(int choice) const
  {
    return choice == correct_answer_index_ + 1;  // +1 because choices are 1-based
  }

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
