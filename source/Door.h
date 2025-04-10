#ifndef DOOR_H
#define DOOR_H

#include "../utilities/Utilities.h"
#include "../utilities/Logger.h"
#include "Interactable.h"
#include "ItemDatabase.h"
#include <string>

class Door{
	
private:
	std::string points_to;
	bool is_locked;
	std::string key_name;
	bool has_been_opened {false};
	
public:
	
	Door(std::string raw_data);
	
	//Methods
	void display();
	void toggle_lock(){is_locked = !is_locked;}
	bool key_matches(std::string key_name) const;
	
	//Getters
	std::string get_points_to(){return points_to;}
	bool get_is_locked(){return is_locked;}
	bool get_has_been_opened(){return has_been_opened;}
	std::string get_key_name(){return key_name;}
	
	//Setters
	void set_is_locked(const bool& locked){is_locked = locked;}
	void set_points_to(std::string room_name){points_to = room_name;}
	
};

#endif