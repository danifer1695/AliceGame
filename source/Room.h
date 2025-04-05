#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <sstream>
#include "Item.h"
#include "Character.h"
#include "Door.h"
#include "Interactable.h"
#include "ItemDatabase.h"
#include "CharacterDatabase.h"
#include "Buffer.h"
#include "../utilities/Logger.h"
#include "../utilities/Utilities.h"
#include "../utilities/Coordinates.h"


class Room: public Interactable{
	
private:
	std::vector<Coordinates> coordinates;
	std::vector<Item> items_vec;
	std::vector<Character> character_vec;
	std::vector<Door> door_vec;
	
	bool is_final_room;
	bool has_been_visited {false};
	
public:
	//Constructors
	Room(): coordinates{}, items_vec{}, Interactable{"Default", "Default"}{};
	Room(std::string name, 
		std::string description, 
		std::vector<Coordinates> coor, 
		std::vector<Item> items_vec, 
		std::vector<Character> char_vec,
		std::vector<Door> doors_vec,
		bool is_final_room_in)
		: Interactable{name, description}, 
		  coordinates{coor}, 
		  items_vec{items_vec}, 
		  character_vec{char_vec},
		  door_vec{doors_vec},
		  is_final_room{is_final_room_in}{};
	
	//Methods
	void add_character(std::string name);
	void remove_character(std::string name);
	void remove_all_enemies();
	void remove_item(std::string name);
	void add_item(std::string name);
	bool has_coordinates(Coordinates coor);
	bool contains_item(std::string name);
	bool contains_character(std::string name);
	bool contains_enemy();
	Item& get_item_by_name(std::string name);
	void transform_room(std::string new_name, std::string new_description, std::vector<Item> new_items_vec);
	void print();
	
	//Debugging
	void display() const;
	
	//Helper methods
	std::string display_coor() const;
	
	//getters
	Coordinates get_coordinates(){return coordinates[0];}
	std::vector<Item>& get_items_vec() {return items_vec;}
	std::vector<Character>& get_character_vec() {return character_vec;}
	std::vector<Door>& get_door_vec() {return door_vec;}
	Door& get_door(std::string door_name);
	bool get_is_final(){return is_final_room;}
	bool get_char_talked_to(std::string name);
	bool get_has_been_visited(){return has_been_visited;}
	Character& get_character_by_name(std::string char_name);
	
	
	//setters
	void set_char_talked_to(std::string name, bool set);
	void set_has_been_visited(bool set){has_been_visited = set;}
};

#endif