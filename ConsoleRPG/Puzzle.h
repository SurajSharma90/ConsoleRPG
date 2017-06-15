#pragma once

#include<string>
#include<vector>
#include<fstream>

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

	const int& getCorrectAns()const { return this->correctAnswer; }
};

