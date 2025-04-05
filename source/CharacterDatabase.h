#ifndef CHARACTER_DATABASE_H
#define CHARACTER_DATABASE_H

#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "../utilities/Utilities.h"
#include "../utilities/Input_Manager.h"
#include "Character.h"

class CharacterDatabase{

private:
	CharacterDatabase(){ load_database();}
	
	std::vector<std::shared_ptr<Character>> character_vec {};
	
public:
	CharacterDatabase(const CharacterDatabase&) = delete;
	CharacterDatabase& operator=(const CharacterDatabase&) = delete;
	
	//Get instance
	static CharacterDatabase& Get();
	
	//Getters
	std::vector<std::shared_ptr<Character>>& get_database(){return character_vec;}
	
	//Methods
	Character& get_character_by_name(std::string name);
	void display();
	
	//Helpers
	void load_database();
	std::vector<std::string> fill_dialogue_vec(const std::string &dialogue_list_raw);
	std::vector<std::string> raw_data_string_to_object_data_string(const std::string &data);
	
};

#endif