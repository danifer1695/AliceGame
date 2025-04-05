#include "ItemDatabase.h"

	std::vector<Item> items {};
//******************************************************************************************************************************
// Constructors
//******************************************************************************************************************************

	ItemDatabase::ItemDatabase(){
		try{
			load_database();
			fill_item_ids_list();
			
		}catch(std::runtime_error &ex){
			GAME_ERROR(ex.what());
		}
	}	
//******************************************************************************************************************************
// Get()
//******************************************************************************************************************************

	ItemDatabase& ItemDatabase::Get(){
		
		static ItemDatabase instance;
		
		return instance;
	}
//******************************************************************************************************************************
// load_database()
//******************************************************************************************************************************
	
	void ItemDatabase::load_database(){
		
		std::string data = Input_Manager::Get().get_raw_data("items");
		
		std::vector<std::string> temp_string_vec = raw_data_string_to_object_data_string(data);
		
		//Now we have a vector with all the item data strings, we just have to create the objects using them
		
		for(std::string str : temp_string_vec){
			
			int id = std::stoi(EXTRACT_STRING(str, 0, "<ID>", "</ID>"));
			std::string name = EXTRACT_STRING(str, 0, "<Name>", "</Name>");
			std::string display = EXTRACT_STRING(str, 0, "<Display>", "</Display");
			std::string description = EXTRACT_STRING(str, 0, "<Description>", "</Description");
			int can_store = std::stoi(EXTRACT_STRING(str, 0, "<Can_Store>", "</Can_Store>"));
			//We convert can_store to a true bool using a conditional expression
			bool can_store_bool = (can_store == 0) ? false : true;
			
			items.push_back(Item(id, name, description, display, can_store_bool));
		}
		
	}
	
//******************************************************************************************************************************
// raw_data_string_to_object_data_string()
//******************************************************************************************************************************
	
	std::vector<std::string> ItemDatabase::raw_data_string_to_object_data_string(const std::string &data){
		
		std::vector<std::string> temp_string_vec;
		//Index where search will start
		size_t index{0};
		size_t end{0};
		std::string temp {};
		
		while(end != std::string::npos && index < data.length()){
			std::string end_string = "</Item>";
			//we find the first end_string
			end = data.find(end_string, index);
			//we extract the item id
			temp = EXTRACT_STRING(data, index, "<Item>", end_string);
			
			//We update the search index
			index = end + end_string.length();
			temp_string_vec.push_back(temp);
		}
		
		return temp_string_vec;
	}
	
//******************************************************************************************************************************
// load_database()
//******************************************************************************************************************************
	
	void ItemDatabase::display(){
		for(auto item : items){
			item.display();
			NEW_LINE;
		}
	}	
//******************************************************************************************************************************
// get_item_by_name()
//******************************************************************************************************************************
	
	Item ItemDatabase::get_item_by_name(std::string name){
		
		
		for(auto item : items){
			
			if(item.contains_name(name)){
				return item;
			}
		}
		throw std::runtime_error("Item " + name + " not found in Item database");
	}
	
//******************************************************************************************************************************
// fill_item_ids_list()
//******************************************************************************************************************************
	
	void ItemDatabase::fill_item_ids_list(){
		for(auto item : items){
			
			//we make the intems name lower case
			std::string lower_case = TO_LOWER(item.get_name());
			
			//and now we add an entry to item_ids
			item_ids[lower_case] = item.get_id();
		}
	}	
	
//******************************************************************************************************************************
// get_item_id()
//******************************************************************************************************************************
	
	int ItemDatabase::get_item_id(std::string name){
		
		int id {9999}; //if the function returns 9999 it means something went wrong
		
		try{
			id = item_ids.at(name); //if .at() fails, it will throw an out of bounds exception.			
		}catch(...){
			GAME_ERROR("ID for item " + name + " not found.");
		}
		return id;
	}