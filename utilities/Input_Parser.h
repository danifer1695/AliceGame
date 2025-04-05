#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <cctype>
#include "Logger.h"
#include "Utilities.h"
#include "../source/Action.h"
#include "../source/Buffer.h"
#include "../source/Player.h"

class Input_Parser{
	
private:
	
	std::string verb;
	std::string preposition;
	std::string object;
	
public:

	Input_Parser(): verb{"default"}, object{"default"}{};
	Input_Parser(std::string input);
	
	bool parse();
	
	//Helper
	void get_words(std::string raw_input);
	
	//Debugging
	void display();
};

#endif