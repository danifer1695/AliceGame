#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <random>
#include <ctime>
#include "Logger.h"

#define EXTRACT_STRING(...) Utilities::extract_string(__VA_ARGS__)
#define EXTRACT_BOOL(...) Utilities::extract_bool(__VA_ARGS__)
#define IFSTREAM_TO_STRING(x) Utilities::ifstream_to_string(x)
#define TO_LOWER(x) Utilities::to_lower(x)
#define ENTER_TO_CONTINUE Utilities::press_to_continue()
#define RANDOM_BINARY Utilities::random_binary()

class Input_Parser;

class Utilities{
	
public:
	static std::string extract_string(const std::string &data, const size_t &pos, const std::string &start_string, const std::string &end_string);
	static bool extract_bool(const std::string &data, const size_t &pos, const std::string &start_string, const std::string &end_string);
	static std::string ifstream_to_string(std::ifstream &in_file);
	static std::string to_lower(const std::string &input);
	static double random_binary();
	static void press_to_continue (); //Press enter to continue
};

#endif