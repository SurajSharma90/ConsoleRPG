#pragma once

#include"STLINCLUDE.h"

class Puzzle
{
private:
	std::string question;
	std::vector<std::string> answers;
	int correctAnswer;

public:
	Puzzle(std::string fileName);
	virtual ~Puzzle();
	std::string getAsString();

	inline const int& getCorrectAns()const { return this->correctAnswer; }
};

