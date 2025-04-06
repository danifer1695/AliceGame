#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include "../utilities/Coordinates.h"
#include "../utilities/Utilities.h"
#include "Player.h"
#include "Buffer.h"
#include "Screen.h"
#include "Events.h"
#include "Map.h"
#include "ItemDatabase.h"
#include "CharacterDatabase.h"

class Action{
	
	enum class Direction{
		North, 
		South,
		East,
		West
	};
	
private:
	
	//helper functions
	static void display_characters(Room& target_room);
	static bool use_key(const std::string& object, const std::string& target);
	static std::string find_matching_key_name(const std::vector<Item>& inventory, const Door& door);
	static void unlock_door(Door& door, const std::string& key_name);
	
public:
	
	static void take(const std::string &input);
	static void move_to(const std::string &input);
	static void inspect(const std::string &input);
	static void talk(const std::string &input);
	static void use(const std::string &input);
	static void drop(const std::string &input);
	static void peek(const std::string &input);
	static void wait();
	static void help();
	static void quit();
	
	
};

#endif