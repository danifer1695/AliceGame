#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <string>
#include <sstream>
#include <vector>
#include "../utilities/Utilities.h"
#include "../utilities/Logger.h"

class Interactable{
	
protected:
	std::vector<std::string> name;
	std::string description;
	
public:
	Interactable(std::string raw_data, std::string description): name{}, description{description} {
		std::stringstream ss (raw_data);
		std::string word;
		
		while(std::getline(ss, word, ',')){
			//remove leading spaces
			size_t start = word.find_first_not_of(" ");
			if(start != std::string::npos)
				word = word.substr(start);
			
			name.push_back(word);
		}
	}
	
	Interactable(std::vector<std::string> name, std::string description)
		: name{name}, description{description} {};
	
	Interactable():Interactable("Default", "Description"){};
	
	//getter
	std::string get_name() const {return name.at(0);}
	std::vector<std::string> get_name_vec() const {return name;}
	std::string get_description() const {return description;}
	
	//setter
	void set_name (std::string new_name){name.at(0) = new_name;}
	
	//debugging
	virtual void display() const = 0;
	
	//methods
	bool contains_name(std::string input_name){
		for(auto str : name){
			if(TO_LOWER(str) == TO_LOWER(input_name))
				return true;
		}
		return false;
	}
};

#endif