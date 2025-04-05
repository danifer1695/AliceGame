#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>
#include "../utilities/Logger.h"
#include "../utilities/Coordinates.h"
#include "../utilities/Input_Manager.h"
#include "../utilities/Input_Parser.h"
#include "ItemDatabase.h"
#include "Map.h"
#include "Buffer.h"
#include "Events.h"
#include "Action.h"
#include "Screen.h"
#include "Player.h"


class Game{
private:	
	
	std::string input;
	
	bool is_running;
	bool Init(); 
	
	void get_inputs();
	void update();
	void draw();
	
public:
	Game();
	~Game() = default;
	
	void Run();
	void set_is_running(bool set){is_running = set;}
};

#endif