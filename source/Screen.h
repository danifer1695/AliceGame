#ifndef SCREEN_H
#define SCREEN_H

#include "Room.h"
#include "Player.h"
#include "Buffer.h"
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>

class Screen{
private:
	
	Screen(){};
	
public:
	
	Screen (const Screen&) = delete;
	Screen& operator=(const Screen&) = delete;
	
	const int width {50};
	
	//Methods
	static Screen& Get();
	void refresh();
	
	//Helper methods
	void display();
	void print_info_panel();
	void print_display_panel();
	void print_menu();
	void prepare_display_panel_contents();
	std::string format_output(std::string to_print);
	
};

#endif
