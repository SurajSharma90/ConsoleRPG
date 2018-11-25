#include <iostream>
#include "test.hpp"

int main()
{
	std::cout << "Hello World!" << "\n";
	Test test;
	std::cout << "Number from Test class: " << test.getNum() << "\n";

	return 0;
}