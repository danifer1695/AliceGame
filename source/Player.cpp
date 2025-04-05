#include "Player.h"



//******************************************************************************************************************************
// initialize()
//******************************************************************************************************************************
	
	Player& Player::Get(){
		
		static Player instance;
		return instance;
	}
	
//******************************************************************************************************************************
// initialize()
//******************************************************************************************************************************

	void Player::initialize(){
		current_room = Map::Get().get_room_at_coor(Coordinates (0, 0));
		if(teleport) GAME_LOG("Teleport active");
	}

//******************************************************************************************************************************
// add_item_to_inventory()
//******************************************************************************************************************************

	bool Player::add_item_to_inventory(int item_id){
		
		
		//We look through the item database for an ID match
		for(auto &item : ItemDatabase::Get().get_database()){
			if(item.get_id() == item_id){
				
				inventory->push_back(item);
				return true;
			}
		}
		return false;
	}
	
	bool Player::add_item_to_inventory(std::string name){
		
		
		//We look through the item database for an ID match
		for(auto item : ItemDatabase::Get().get_database()){
			for(auto& str : item.get_name_vec()){
				
				if(TO_LOWER(str) == TO_LOWER(name)){
					
					inventory->push_back(item);
					return true;
				}
			}
		}
		return false;
	}
//******************************************************************************************************************************
// add_item_to_inventory()
//******************************************************************************************************************************

	bool Player::remove_item_from_inventory(std::string name){
		
		if(inventory->empty()){
			GAME_ERROR("Could not remove item \"" + name + "\". Inventory empty.");
			return false;
		}
			
		for(int i = 0; i < inventory->size(); i++){
			
			for(auto& str : inventory->at(i).get_name_vec()){
				
				if(TO_LOWER(str) == name){
					inventory->erase(inventory->begin() + i);
					return true;
				}
			}
		}
		
		GAME_ERROR("Could not remove item \"" + name + "\". Item not found.");
		return false;
	}
//******************************************************************************************************************************
// display_inventory()
//******************************************************************************************************************************

	std::string Player::display_inventory(){
		
		std::ostringstream oss {};
		oss << "Inventory contents:\n";
		
		for(auto &item : *inventory){
			oss << "-" << item.get_name() << "\n";
		}
		
		return oss.str();
	}

//******************************************************************************************************************************
// contains_item_in_inventory()
//******************************************************************************************************************************

	bool Player::contains_item_in_inventory(std::string name){
		
		for(auto item : *inventory){
			//loop through all the names an object has
			if(item.contains_name(name))
				return true;
		}
		return false;
	}
	
//******************************************************************************************************************************
// set_current_room()
//******************************************************************************************************************************

	void Player::set_current_room(const std::string &name){
		
		try{
			set_current_room(Map::Get().get_room(name));			
		}catch(std::exception &ex){
			GAME_ERROR(ex.what());
		}
	}
	
//******************************************************************************************************************************
// get_treasure_ui()
//******************************************************************************************************************************

	std::string Player::get_treasure_ui(){
		
		if(!treasure_quest_started){
			return "- ???";
		}else if(treasure_completed){
			return "COMPLETED";
		}
		else{
			std::string to_return = "- Treasure (" + std::to_string(treasure_collected) + "/" + std::to_string(treasure_goal) + ")";
			return to_return;
		}
	}
	
//******************************************************************************************************************************
// get_sweets_ui()
//******************************************************************************************************************************

	std::string Player::get_sweets_ui(){
		
		if(!sweets_quest_started){
			return "- ???";
		}else if(sweets_completed){
			return "COMPLETED";
		}else{
			std::string to_return = "- Sweets (" + std::to_string(sweets_collected) + "/" + std::to_string(sweets_goal) + ")";
			return to_return;
		}
	}