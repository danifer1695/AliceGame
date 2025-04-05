#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <string>

#include "../utilities/Utilities.h"
#include "../utilities/Logger.h"
#include "../utilities/Coordinates.h"
#include "DialogueDatabase.h"
#include "ItemDatabase.h"
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include "Map.h"
#include "Buffer.h"

//forward declare Game to avoid circular dependencies
class Game;

class Events{
	
private:
	
	Events(){};
	Game* game; //reference to running game instance
	
public:
	//Detele copy constructor and assign operator
	Events(const Events&) = delete;
	Events& operator=(const Events&) = delete;
	
	//Instance caller
	static Events& Get();
	
	//methods
	void game_intro();
	void get_caught();
	void get_caught_game_over();
	void unlock_door(Door& door);
	void end_game();
	void cheshire_first_encounter();
	void random_character_spawn(const std::string& room);
	void get_diamond_key();
	void dark_room_transform();
	void wear_uniform();
	void unlock_armory();
	void talk_to_cheshire();
	void talk_to_fox();
	void help();
	Door& choose_door();
	bool armory_distraction();
	bool guard_permit_check();
	
	void set_game_instance(Game* game_instance){game = game_instance;}
	
};

#endif