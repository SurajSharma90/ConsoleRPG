#include "Puzzle.h"

Puzzle::Puzzle(std::string fileName)
{
	//SAVE/LOAD FORMAT
	/*
	Question
	nrOfAns
	answers
	correctAns
	*/

	this->correctAnswer = 0;

	std::ifstream inFile(fileName);
	
	int nrOfAns = 0;
	std::string answer = "";
	int correctAns = 0;

	if (inFile.is_open())
	{
		std::getline(inFile, this->question);
		inFile >> nrOfAns;
		inFile.ignore();

		for (size_t i = 0; i < nrOfAns; i++)
		{
			std::getline(inFile, answer);
			this->answers.push_back(answer);
		}

		inFile >> correctAns;
		this->correctAnswer = correctAns;
		inFile.ignore();
	}
	else
		throw("Could not open puzzle!");

	inFile.close();
}

Puzzle::~Puzzle()
{

}

std::string Puzzle::getAsString()
{
	std::string answers = "";

	for (size_t i = 0; i < this->answers.size(); i++)
	{
		answers += std::to_string(i) + ": " + this->answers[i] + "\n";
	}

	/*return this->question + "\n" + "\n"
		+ answers + "\n"
		+ std::to_string(this->correctAnswer) + "\n";*/

	return this->question + "\n" + "\n"
		+ answers + "\n";
}
