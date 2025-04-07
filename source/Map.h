#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <regex>

#include "../utilities/Utilities.h"
#include "../utilities/Coordinates.h"
#include "../utilities/Input_Manager.h"
#include "Door.h"
#include "Item.h"
#include "Room.h"
#include "Character.h"
#include "ItemDatabase.h"
#include "CharacterDatabase.h"

class Player;

class Map{
	
private:
	Map();
	std::string data {};
	std::vector<std::shared_ptr<Room>> room_vec {};
	
public:
	Map(const Map &map) = delete;
	Map& operator=(const Map&) = delete;
	
	static Map& Get();
	
	//Debugging
	void display();
	
	//Getters
	std::shared_ptr<Room> get_room_at(int index) const{return room_vec[index];}
	std::shared_ptr<Room> get_room_at_coor(Coordinates coor) const;
	std::shared_ptr<Room> get_room(const std::string &name);
	
	//methods
	bool contains_room(std::string name);
	
	//Helper methods
	std::vector<std::string> raw_data_string_to_object_data_string(const std::string &data);
	void load_database();
	std::vector<Coordinates> extract_coordinates(const std::string& input);
	std::vector<Item> fill_items_vec(const std::string &item_list_raw);
	std::vector<Character> fill_character_vec(const std::string &raw_data);
	std::vector<Door> fill_door_vec(const std::string &raw_data);
};



#endif