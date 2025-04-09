#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include "Room.h"
#include "Map.h"
#include "ItemDatabase.h"
#include "../utilities/Logger.h"
#include "../utilities/Utilities.h"


class Player{

private: 
	
	Player() {};
	
	std::string name {"Alice"};
	bool disguised {false};
	int current_day {1};
	int max_days {7};
	std::shared_ptr<Room> current_room;
	std::shared_ptr<Room> previous_room;
	std::shared_ptr<std::vector<Item>> inventory = std::make_shared<std::vector<Item>>();
	
	//Collectibles
	bool treasure_quest_started {false};
	int treasure_goal {3};
	int treasure_collected {0};
	bool treasure_completed {false};
	
	bool sweets_quest_started {false};
	int sweets_goal {2};
	int sweets_collected {0};
	bool sweets_completed {false};
	
	//debugging
	bool teleport {false};
	
public:

	Player(const Player &player) = delete;
	Player& operator=(const Player&) = delete;
	
	static Player& Get();
	
	void initialize();
	
	//Inventory
	std::string display_inventory();
	bool add_item_to_inventory(int item_id);
	bool add_item_to_inventory(std::string name);
	bool remove_item_from_inventory(std::string name);
	bool contains_item_in_inventory(std::string name);
	
	//getters
	int get_current_day() {return current_day;}
	int get_max_days() {return max_days;}
	std::shared_ptr<Room>& get_current_room() {return current_room;}
	std::shared_ptr<Room>& get_previous_room() {return previous_room;}
	std::shared_ptr<std::vector<Item>> get_inventory() {return inventory;}
	bool can_teleport() {return teleport;}
	bool is_disguised() {return disguised;}
	
	int get_treasure_goal() {return treasure_goal;}
	int get_treasure_collected() {return treasure_collected;}
	int get_remaining_treasure() {return treasure_goal - treasure_collected;}
	bool get_treasure_completed() {return treasure_completed;}
	
	int get_sweets_goal() {return sweets_goal;}
	int get_sweets_collected() {return sweets_collected;}
	int get_remaining_sweets() {return sweets_goal - sweets_collected;}
	bool get_sweets_completed() {return sweets_completed;}
	
	//setters
	void set_current_room(const std::shared_ptr<Room> &room){current_room = room;}
	void set_previous_room(const std::shared_ptr<Room> &room){previous_room = room;}
	void set_current_room(const std::string &name); //set by name
	void set_current_day(const int &day){current_day = day;}
	void set_disguised(const bool &input){disguised = input;}
	void set_treasure_quest_started(bool set){treasure_quest_started = set;}
	void set_treasure_completed(bool set){treasure_completed = set;}
	void set_sweets_quest_started(bool set){sweets_quest_started = set;}
	void set_sweets_completed(bool set){sweets_completed = set;}
	void set_teleport(bool set){teleport = set;}
	
	//Methods
	void add_treasure_collected() {treasure_collected++;}
	void add_sweets_collected() {sweets_collected++;}
	std::string get_treasure_ui ();
	std::string get_sweets_ui ();

};

#endif