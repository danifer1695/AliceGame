#include "Door.h"

	
//******************************************************************************************************************************
// Constructor()
//******************************************************************************************************************************
	
	Door::Door(std::string raw_data){
		
		points_to = EXTRACT_STRING(raw_data, 0, "<To>", "</To>");
		int locked_int = std::stoi(EXTRACT_STRING(raw_data, 0, "<Locked>", "</Locked>"));
		key_name = EXTRACT_STRING(raw_data, 0, "<Key>", "</Key");
		is_locked = (locked_int == 0) ? false : true;
	
	}
	
//******************************************************************************************************************************
// key_matches()
//******************************************************************************************************************************
	
	bool Door::key_matches(std::string input_key_name){
		
		for(auto& name : ItemDatabase::Get().get_item_by_name(key_name).get_name_vec()){
			
			if(TO_LOWER(name) == input_key_name)
				return true;
		}
		return false;
	}
	
//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void Door::display(){
		
		GAME_PRINT("Door to: " + points_to + ". Is it locked?: " + ((is_locked) ? "Yes" : "No") + ".\n")
	}