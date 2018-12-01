#include "gui_functions.h"

const std::string gui::menu_title(const std::string title)
{
	std::stringstream ss;

	ss << "= " << title << " ="
		<< "\n"
		<< "\n";

	return ss.str();
}

const std::string gui::menu_divider(const unsigned amount, const char symbol)
{
	std::stringstream ss;

	ss << std::string(amount, symbol) 
		<< "\n" 
		<< "\n";

	return ss.str();
}

const std::string gui::menu_item(const unsigned index, const std::string text)
{
	std::stringstream ss;

	ss << "- " << "(" << index << ") " << text
		<< "\n";

	return ss.str();
}