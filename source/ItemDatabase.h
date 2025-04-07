#ifndef ITEM_LIBRARY_
#define ITEM_LIBRARY_

#define ITEM_BARREL		1000
#define ITEM_KEY		1001

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include "Item.h"
#include "../utilities/Utilities.h"
#include "../utilities/Input_Manager.h"
#include "../utilities/Logger.h"

class ItemDatabase {
	
private:
	ItemDatabase();
	std::vector<Item> items;
	
	//here we will store every item's name (key), and id(value). 
	//the name will be in all lower case.
	std::unordered_map<std::string, int> item_ids {};
	
public:
	//Singleton - Delete copy constructor and = operator
	ItemDatabase(const Input_Manager&) = delete; 
	ItemDatabase& operator=(const Input_Manager&) = delete;
	
	static ItemDatabase& Get();
	Item get_item_by_name(std::string name);
	int get_item_id(std::string name);
	bool item_is_of_type(std::string input, std::string type);
	
	//Getters
	std::vector<Item> get_database() {return items;}
	
	//Helper
	std::vector<std::string> raw_data_string_to_object_data_string(const std::string &data);
	void load_database();
	void fill_item_ids_list();
	void display();
	
};

#endif