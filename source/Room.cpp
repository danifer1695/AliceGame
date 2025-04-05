#include "Room.h"


//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void Room::display() const{
		std::string message ("Room " + 
			get_name() + " is at coordinates " + display_coor() + " and reads: \"" + description + "\".\n");
			
		GAME_PRINT(message);
		GAME_PRINT("It contains these items: ");
		
		std::string item_message;
		for(auto item : items_vec){
			item_message += (item.get_name() + " ");
		}
		
		GAME_PRINT(item_message + "\n");
		GAME_PRINT("It contains these characters: ");
		
		std::string char_message;
		for(auto character : character_vec){
			char_message += (character.get_name() + " ");
		}
		
		GAME_PRINT(item_message + "\n");
		GAME_PRINT("It contains these doors:\n");
		
		for(auto door : door_vec){
			door.display();
		}
		
	}
	
//******************************************************************************************************************************
// print()
//******************************************************************************************************************************
	
	void Room::print(){
		//if its the first time the player enters the room, display full description. After that,
		//we display just a quick message
		if(!has_been_visited){
			
			Buffer::Get().add_contents("You are in ");
			Buffer::Get().add_contents(description + "\n\n");
		}
		else
			Buffer::Get().add_contents("You're back in the " + get_name() + ".\n\n");
			
		//Display the items
		if(!items_vec.empty()){
			
			bool visible_item_found {false};
			
			for(auto &item : items_vec){
				
				if(item.get_display() != ""){
					
					Buffer::Get().add_contents(item.get_display() + "\n");
					visible_item_found = true;
				}
			}
			//add extra line only if there are items to show
			if(visible_item_found) Buffer::Get().add_contents("\n"); 
		}
		
		//display the characters
		if(!character_vec.empty()){
		
			Buffer::Get().add_contents("These characters are present:\n");
			
			for(auto &character : character_vec){
				Buffer::Get().add_contents("-" + character.get_name());
				//show if a character is not conscious.
				if(!character.get_is_conscious()) Buffer::Get().add_contents(" (passed out)");
				
				Buffer::Get().add_contents("\n");
			}
			Buffer::Get().add_contents("\n");
			
		}
		
		//Display the doors 
		if(!door_vec.empty()){
			for(auto &door : door_vec){
				
				Buffer::Get().add_contents("There is a door to the " + door.get_points_to() + ".\n");
			}
		}
		
	}
	
	
//******************************************************************************************************************************
// display_coor()
//******************************************************************************************************************************
	
	std::string Room::display_coor() const{
		
		std::string str {};
		
		for(const Coordinates coor : coordinates){
			str.append(coor.display());
		}
		
		return str;
	}
	
//******************************************************************************************************************************
// has_coordinates()
//******************************************************************************************************************************

	bool Room::has_coordinates(Coordinates coor){
		
		for(auto obj : coordinates){
			if(coor.x == obj.x && coor.y == obj.y)
				return true;
		}
		return false;
	}

//******************************************************************************************************************************
// remove_item()
//******************************************************************************************************************************
	
	void Room::remove_item(std::string name){
		Item *ptr = nullptr;
		
		
		for(auto &item : items_vec){
			//check if any of the item's names match
			for(auto& str : item.get_name_vec()){
				if(TO_LOWER(str) == TO_LOWER(name)){

					ptr = &item;
				}
			}
		} 
		if(ptr == nullptr){
			GAME_ERROR("Error at:"); //we use GAME_ERROR so we get this exact line number printed on the console.
			throw std::runtime_error("Error removing item from room object. Item " + name + " not found.");
		}
		
		//GAME_LOG(ptr->get_name() + " removed!");
		items_vec.erase(find(items_vec.begin(), items_vec.end(), *ptr));
		
	}
	
//******************************************************************************************************************************
// add_item()
//******************************************************************************************************************************
	
	void Room::add_item(std::string name){
		
		items_vec.push_back(ItemDatabase::Get().get_item_by_name(name));
	}
	
//******************************************************************************************************************************
// contains_item()
//******************************************************************************************************************************
	
	bool Room::contains_item(std::string name){
		
		for(auto item : items_vec){
			if(item.contains_name(name))
				return true;
		}
		return false;
	}	
//******************************************************************************************************************************
// contains_character()
//******************************************************************************************************************************
	
	bool Room::contains_character(std::string name){
		
		for(auto character : character_vec){
			if(character.contains_name(name))
				return true;
		}
		return false;
	}	
	
//******************************************************************************************************************************
// contains_enemy()
//******************************************************************************************************************************
	
	bool Room::contains_enemy(){
		
		//display();
		
		for(auto character : character_vec){
			if(character.get_is_enemy() &&
				character.get_is_conscious()){
				
				return true;
			}
		}
		return false;
	}
	
//******************************************************************************************************************************
// get_char_talked_to()
//******************************************************************************************************************************
	
	bool Room::get_char_talked_to(std::string name){
		
		for(auto& character : character_vec){
			if(TO_LOWER(character.get_name()) == name)
				return character.get_talked_to();
		}
		
		GAME_ERROR("Character " + name + " not found.");
		return false;
	}
	
//******************************************************************************************************************************
// set_char_talked_to()
//******************************************************************************************************************************
	
	void Room::set_char_talked_to(std::string name, bool set){
		
		for(auto &character : character_vec){
			
			if(TO_LOWER(character.get_name()) == name){
				
				character.set_talked_to(set);
				return;
			}
		}
		
		GAME_ERROR("Character " + name + " not found.");
	}
//******************************************************************************************************************************
// add_character()
//******************************************************************************************************************************
	
	void Room::add_character(std::string name){
		
		character_vec.push_back(CharacterDatabase::Get().get_character_by_name(name));
		
	}
	
//******************************************************************************************************************************
// remove_character()
//******************************************************************************************************************************
	
	void Room::remove_character(std::string name){
		
		Character *ptr = nullptr;
		
		
		for(auto &character : character_vec){
			if(character.get_name() == name){
				
				ptr = &character;
			}
		} 
		if(ptr == nullptr){
			GAME_ERROR("Error at:"); //we use GAME_ERROR so we get this exact line number printed on the console.
			throw std::runtime_error("Error removing character from room object. Character \"" + name + "\" not found.");
		}
		
		character_vec.erase(find(character_vec.begin(), character_vec.end(), *ptr));
	}
	

//******************************************************************************************************************************
// remove_all_enemies()
//******************************************************************************************************************************
	
	void Room::remove_all_enemies(){
		
		for(auto character = character_vec.begin(); character != character_vec.end();){
			if(character->get_is_enemy())
				character = character_vec.erase(character); //erase() returns the next valid iterator
			else
				++character; //only delete if no deletion happened
		}
	}
	

//******************************************************************************************************************************
// get_item_by_name()
//******************************************************************************************************************************
	
	Item& Room::get_item_by_name(std::string name){
		
		for(auto& item : items_vec){
			for(auto& str : item.get_name_vec()){
				
				if(TO_LOWER(str) == name)
					return item;
			}
		}
		throw std::runtime_error("Item " + name + " not found at FILE: Room.cpp - FUNC: get_item_by_name()");
	}

//******************************************************************************************************************************
// transform_room()
//******************************************************************************************************************************
	
	void Room::transform_room(std::string new_name, std::string new_description, std::vector<Item> new_items_vec){
		
		set_name(new_name);
		description = new_description;
		items_vec = new_items_vec;
	}

//******************************************************************************************************************************
// get_door()
//******************************************************************************************************************************
	
	Door& Room::get_door(std::string door_name){
		
		std::vector<Door>::iterator it = door_vec.begin();
		
		while(it != door_vec.end()){
			if(TO_LOWER(it->get_points_to()) == TO_LOWER(door_name)){
				return *it; // Returns a reference to the found Door
			}
			++it; //Move it to next element
		}
		
		throw std::runtime_error("Door to " + door_name + " not found in Room " + get_name());
	}
	

//******************************************************************************************************************************
// get_character_by_name()
//******************************************************************************************************************************
	
	Character& Room::get_character_by_name(std::string char_name){
		
		for(auto& character : character_vec){
			if (character.contains_name(char_name))
				return character;
		}
		
		throw std::runtime_error("Character " + char_name + " not found in Room::get_character_by_name().");
	}
	

//******************************************************************************************************************************
// ()
//******************************************************************************************************************************
