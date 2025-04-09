#include "Action.h"

//******************************************************************************************************************************
// move_to()
//******************************************************************************************************************************

	void Action::move_to(const std::string &input){
		
		std::shared_ptr<Room> current_room = Player::Get().get_current_room();
		std::shared_ptr<Room> previous_room = Player::Get().get_previous_room();
		
		bool found {false};//checks whether the input is a valid room
		
		if(input == "back" || input == "last room" || input == "previous room"){
			
			if(previous_room != nullptr) 
				Player::Get().set_current_room(previous_room);
			else
				Buffer::Get().add_contents("Go back where?\n\n");
				
			previous_room->print();
			return;
		}
		
		if(input == "door"){
			
			Door* door = Events::Get().choose_door();
			//check whether door is locked, if it is, return.
			if(door->get_is_locked() && !Player::Get().can_teleport()){
				if(!door->get_key_name().empty())
					Buffer::Get().add_contents("The door is locked. It needs a " + door->get_key_name() + ".\n\n");
				else
					Buffer::Get().add_contents("The door is locked from the other side.\n\n");
					
				current_room->print();
				return;
			}
			
			Player::Get().set_current_room(door->get_points_to());
			current_room = Player::Get().get_current_room();
			current_room->print();
			return;
		}
		
		//if name is invalid
		if(!Map::Get().contains_room(input)){
			Buffer::Get().add_contents("Go where?\n\n");
			GAME_ERROR("Room \"" + input + "\" not found.");
			current_room->print();
			return;
		}
		
		//When we go to the Outside, first we check the player holds the permit, by calling Events::guard_permit_check
		if(current_room->get_name() == "Staff Hall" &&
		  input == "outside"){
			
			//if player holds the Break Permit, they will be allowed to leave
			if(!Events::Get().guard_permit_check()){
				
				current_room->print();
				return;
			}
		 }
		
		//We unlock door to Staff hall in Armory when entering Armory from Staff Hallway
		if(current_room->get_name() == "Staff Hall" &&
		   current_room->contains_character("Card Guard") &&
		   input == "armory"){
			
				Events::Get().unlock_armory();
				//update current room pointer
				current_room = Player::Get().get_current_room();
		}

		//we look for room names in available doors.
		for(auto& door : current_room->get_door_vec()){
			if(Map::Get().get_room(door.get_points_to())->contains_name(input) || Player::Get().can_teleport()){
				
				found = true;
				if(door.get_is_locked() && !Player::Get().can_teleport()){
					if(!door.get_key_name().empty())
						Buffer::Get().add_contents("The door is locked. It needs a " + door.get_key_name() + ".\n\n");
					else
						Buffer::Get().add_contents("The door is locked from the other side.\n\n");
						
					break;
				}
				
				//set room to visited before we change current rooms
				if(!current_room->get_has_been_visited())
					current_room->set_has_been_visited(true);	
				
				//set current room to the one we're going to
				Player::Get().set_current_room(input);
				current_room = Player::Get().get_current_room();
				break;
			}
		}
		
		//if a room with the entered name is not found
		if(!found){
			Buffer::Get().add_contents("Go where?\n\n");
			GAME_ERROR("Room \"" + input + "\" not found.");
			current_room->print();
			return;
		}
	
		//Check if there is an enemy in the room
		if(current_room->contains_enemy() &&
		   !Player::Get().is_disguised()){
				GAME_LOG("Enemy present.");
				Buffer::Get().add_contents("As you step into the room a Card Guard notices you:\n");
				Events::Get().get_caught();
				//update current room pointer
				current_room = Player::Get().get_current_room();
			
		}
		//Check if new room is the final room which ends the game.
		if(current_room->get_is_final()){
			GAME_LOG("Player made it to the goal.");
			Events::Get().end_game();
			return;
		}
		
		//Random enemy spawn every time we change room, except when moving into
		//the room where the spawning happens
		if(current_room->get_name() != "Staff Hallway"){
			Events::Get().random_character_spawn("Staff Hallway");
		}
		
		//When we move to a new room we automatically display
		current_room->print();
		
	}


//******************************************************************************************************************************
// take()
//******************************************************************************************************************************

	void Action::take(const std::string &input){
		
		//we use that id to remove the item from the current room, using Room'
		//remove_item() method
		try{
			std::string item_name = Player::Get().get_current_room()->get_item_by_name(input).get_name();	
			std::string item_name_lower = TO_LOWER(item_name);	
			
			//check if item can be stored
			if(!ItemDatabase::Get().get_item_by_name(item_name_lower).get_store()){
				
				Buffer::Get().add_contents("That item cannot be stored.\n\n");
				throw std::runtime_error ("That item cannot be stored.");
			}
			
			Player::Get().add_item_to_inventory(item_name_lower);
			
			Player::Get().get_current_room()->remove_item(item_name_lower);
			
			Buffer::Get().add_contents("You added " + item_name + " to your inventory.\n\n");
		}
		
		catch(std::exception &ex){
			
			GAME_ERROR(ex.what());
			Buffer::Get().add_contents("There is no " + input + " around to take.\n\n");
		}
			
		
		Buffer::Get().add_contents("Press enter to continue.");
		Screen::Get().refresh();
		ENTER_TO_CONTINUE;
		
	}


//******************************************************************************************************************************
// talk()
//******************************************************************************************************************************

	void Action::talk(const std::string &input){
		
		std::shared_ptr<Room> current_room = Player::Get().get_current_room();
		
		if(current_room->contains_character(input)){
			
			Character* character = &current_room->get_character_by_name(input);
			
			std::string char_name = TO_LOWER(character->get_name());
			
			if(CharacterDatabase::Get().get_character_by_name("Cheshire Cat").contains_name(input)){
				
				Events::Get().talk_to_cheshire();
				return;
				
			}else if(CharacterDatabase::Get().get_character_by_name("Cunning Fox").contains_name(input)){
				
				Events::Get().talk_to_fox();
				return;
				
			}else if(CharacterDatabase::Get().get_character_by_name("Card Guard").contains_name(input) &&
				current_room->contains_name("Staff Hall")){ //we specify staff hall cause we only want thit to apply to the guard in that room.
				
				Buffer::Get().add_contents(dialogue_database.at("Guard_02"));
				Buffer::Get().add_contents("\n\nPress enter to continue.");
				
				Screen::Get().refresh();
				ENTER_TO_CONTINUE;
				return;
				
			}else{
				
				Buffer::Get().add_contents(character->get_dialogue());
				Buffer::Get().add_contents("\n\nPress enter to continue.");
				
				Screen::Get().refresh();
				ENTER_TO_CONTINUE;
				
				if(!character->get_talked_to()){
					character->set_talked_to(true);
				}
				
				return;
			}
			
		}else{
			GAME_ERROR("Character " + input + " was not found.");
			Buffer::Get().add_contents("Talk to whom?\n\n");
		}
		
		Player::Get().get_current_room()->print();
	}

//******************************************************************************************************************************
// inspect()
//******************************************************************************************************************************

	void Action::inspect(const std::string &input){
		
		std::shared_ptr<Room> current_room = Player::Get().get_current_room();
		
		//Input Parser class sends input in all lower case.
		//No need to account for case variations
		if (input == "room" || input == "surroundings" || input == "around"){
			
			Buffer::Get().add_contents("You're in a ");
			Buffer::Get().add_contents(current_room->get_description());
			Buffer::Get().add_contents("\n\nPress enter to continue.");
		
			Screen::Get().refresh();
			ENTER_TO_CONTINUE;
			return;
		}
		else if(input == "door"){
			
			Door* door = Events::Get().choose_door();
			Buffer::Get().add_contents("Its a door that leads to the " + door->get_points_to() + ".");
			Buffer::Get().add_contents("\n\nPress enter to go back.");
			
			Screen::Get().refresh();
			ENTER_TO_CONTINUE;
			return;
		}
		else if(input == "inventory"){
			Buffer::Get().add_contents(Player::Get().display_inventory());
			Buffer::Get().add_contents("\n\nPress enter to go back.");
			
			Screen::Get().refresh();
			ENTER_TO_CONTINUE;
			return;
		}
		else{
			if(current_room->contains_item(input) ||
				Player::Get().contains_item_in_inventory(input)){
				
				std::string description = ItemDatabase::Get().get_item_by_name(input).get_description();
				Buffer::Get().add_contents(description);
				Buffer::Get().add_contents("\n\nPress enter to continue.");
				
			}else if(current_room->contains_character(input)){
				
				Buffer::Get().add_contents(CharacterDatabase::Get().get_character_by_name(input).get_description());
				Buffer::Get().add_contents("\n\nPress enter to continue.");
			}else{
				Buffer::Get().add_contents("There isn't a " + input + " to inspect.");
				Buffer::Get().add_contents("\n\nPress enter to continue.");
				
				Screen::Get().refresh();
				ENTER_TO_CONTINUE;
				return;
			}
		}
	}
	
//******************************************************************************************************************************
// use()
//******************************************************************************************************************************

	void Action::use(const std::string &input){
		
		std::string object, target; 
		
		second_parsing(object, target, input);
		
		bool action_success {false};//we will use this to check if action was successful
		
		//All uses are hardcoded for the moment. If items change names in item list, they much be changed
		//here as well
		
		//first we check that the player has an object of this name in their inventory
		if(Player::Get().contains_item_in_inventory(object)){
			
			//if object is of type key and it matches, return and exit
			if(ItemDatabase::Get().item_is_of_type(object, "key")){
				
				action_success = use_key(object, target);
			}
				
			//if firecracker is used on armory, we call armory_distraction event
			else if(ItemDatabase::Get().item_is_of_type(object, "firecracker") && 
				(target == "armory" || target == "weapons" || target == "shields" || target == "shield" || target.empty())){
				
						action_success = Events::Get().armory_distraction();
						
			}	
			
			//if spear is used on key chain
			else if(ItemDatabase::Get().get_item_by_name("Spear").contains_name(object) && 
					Player::Get().get_current_room()->get_name() == "Broom Closet" &&
					ItemDatabase::Get().get_item_by_name("Key Chain").contains_name(target)){
						
						Events::Get().get_diamond_key();
						action_success = true;
			}
			//if lamp is used in the Dark room
			else if(ItemDatabase::Get().get_item_by_name("Oil Lamp").contains_name(object)&& 
					Player::Get().get_current_room()->get_name() == "Dark Room" &&
					(target == "room" || target == "dark room"|| target == "")){
						
						Events::Get().dark_room_transform();
						action_success = true;
			}
			//if servant uniform is used
			else if(ItemDatabase::Get().get_item_by_name("Servant Uniform").contains_name(object)){
						
						Player::Get().remove_item_from_inventory(object);
						Screen::Get().refresh();
						ENTER_TO_CONTINUE;
						return;
			}
			//if beverage is used
			else if(ItemDatabase::Get().get_item_by_name("Beverage").contains_name(object)){
						
						Buffer::Get().add_contents("You wouldn't want to drink that. It seems to leave the guards all sleepy!");
						Buffer::Get().add_contents("\n\nPress enter to continue.");
						
						Player::Get().remove_item_from_inventory(object);
						Screen::Get().refresh();
						ENTER_TO_CONTINUE;
						return;
			}else{
				
				Buffer::Get().add_contents("You can't use your " + object + " like that.\n\n");
			}	
		}
		//if player does not have an object of that name in their inventory
		else{
			
			GAME_ERROR("Item " + object + " not found. Does the name match the one in item_data?");
			Buffer::Get().add_contents("Use what?\n\n");
		}
		
		//Remove item from inventory
		if(action_success){
			Player::Get().remove_item_from_inventory(object);
		}
		
		Player::Get().get_current_room()->print();
	}	
	
//******************************************************************************************************************************
// drop()
//******************************************************************************************************************************

	void Action::drop(const std::string &input){
		
		if(Player::Get().contains_item_in_inventory(input)){
			//Remove item from player inventory
			Player::Get().remove_item_from_inventory(input);
			//Add item to the room item vector
			Player::Get().get_current_room()->add_item(input);
			
			std::string item_name = ItemDatabase::Get().get_item_by_name(input).get_name();
			Buffer::Get().add_contents( item_name + " dropped.\n\n");
		}else{
			Buffer::Get().add_contents( "Drop what?\n\n");
		}
		
		Player::Get().get_current_room()->print();
	}	
	
//******************************************************************************************************************************
// peek()
//******************************************************************************************************************************

	void Action::peek(const std::string &input){
		
		for(auto& door : Player::Get().get_current_room()->get_door_vec()){
			if(input == TO_LOWER(door.get_points_to())){
				
				Buffer::Get().add_contents("You peek through the door's key hole:\n");
				Buffer::Get().add_contents("You see the " + Map::Get().get_room(input)->get_name() + ". It's ");
				Buffer::Get().add_contents(Map::Get().get_room(input)->get_description() + "\n\n");
				
				display_characters(*Map::Get().get_room(input));
				
				Buffer::Get().add_contents("\nPress enter to continue.");
				
				Screen::Get().refresh();
				ENTER_TO_CONTINUE;
				return;
			}
		}
		
		Buffer::Get().add_contents("No door leads to such room.\n\n");
		Player::Get().get_current_room()->print();
	}
	
//******************************************************************************************************************************
// wait()
//******************************************************************************************************************************

	void Action::wait(){
		
		Buffer::Get().add_contents("You wait for a while. Time passes...\n\n");
		Buffer::Get().add_contents("Press enter to continue");
		Events::Get().random_character_spawn("Staff Hallway");
		Screen::Get().refresh();
		
		ENTER_TO_CONTINUE;
	}
	
//******************************************************************************************************************************
// help()
//******************************************************************************************************************************

	void Action::help(){
		
		Events::Get().help();
		Player::Get().get_current_room()->print();
	}
	
//******************************************************************************************************************************
// quit()
//******************************************************************************************************************************

	void Action::quit(){
		
		Buffer::Get().add_contents("Quitting game. Goodbye.");
		Screen::Get().refresh();
		throw 0;
	}
	
//******************************************************************************************************************************
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~HELPER METHODS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//******************************************************************************************************************************
//******************************************************************************************************************************
// display_characters()
//******************************************************************************************************************************

	void Action::display_characters(Room& target_room){
		
		//Display contained character's information
			if(!target_room.get_character_vec().empty()){
			
				Buffer::Get().add_contents("These characters are present:\n");
				
				for(auto &character : target_room.get_character_vec()){
					Buffer::Get().add_contents("-" + character.get_name());
					//show if a character is not conscious.
					if(!character.get_is_conscious()) Buffer::Get().add_contents(" (passed out)");
					
					Buffer::Get().add_contents("\n");
				}
				Buffer::Get().add_contents("\n");
				
			}
	}
	
	
//******************************************************************************************************************************
// display_characters()
//******************************************************************************************************************************

	bool Action::use_key(const std::string& object, const std::string& target){
		
		auto inventory = Player::Get().get_inventory();
		
		for(auto& item : *inventory){
			
			//if the item does not match the input, continue the loop
			if(!item.contains_name("key") || !item.contains_name(object)) continue;
			
			//if player types "door" or just "use key/key name"
			if(target == "door" || target == "the door" || target.empty()){
			
				try{					
					//this gives the player a list of available doors and returns their choice
					Door* door = Events::Get().choose_door();
					std::string key_name = (object == "key") ? find_matching_key_name(*inventory, *door) : object;
					
					if(!key_name.empty() && door->key_matches(key_name)){
						unlock_door(*door, key_name);
						return true;
					}
					
					Buffer::Get().add_contents("The key did not work on that door.\n\n");
					return false;
					
				}catch(std::exception &ex){
					Buffer::Get().add_contents("There is no such Door!\n\n");
					return false;
				}
			}
				
			//if player types in the name of the room directly
			for(auto& door : Player::Get().get_current_room()->get_door_vec()){
				
				//we check every door in the room to see if its name matches the input
				if(target == TO_LOWER(door.get_points_to()) && 
					door.get_is_locked()){
					
					std::string key_name = (object == "key") ? find_matching_key_name(*inventory, door) : object;
					
					if(!key_name.empty() && door.key_matches(key_name)){
						unlock_door(door, key_name);
						return true;
					}
				}
			}
			
		}
		
		//if action was unsuccessful we print a message letting the player know
		Buffer::Get().add_contents("Sorry, I don't know what \"" + target + "\" is.\n\n");
		return false;
	}
	
//******************************************************************************************************************************
// std::string Action::find_matching_key_name()
//******************************************************************************************************************************

	std::string Action::find_matching_key_name(const std::vector<Item>& inventory, const Door& door){
		
		//we check every item in the inventory. first if they contain the name "key", and second if their 
		//main name matches the selected door key.
		for(const auto& item : inventory){
			if(item.contains_name("key") && door.key_matches(item.get_name()))
				return TO_LOWER(item.get_name());
		}
		
		return "";
	}

//******************************************************************************************************************************
// display_characters()
//******************************************************************************************************************************

	void Action::unlock_door(Door& door, const std::string& key_name){
		
		door.toggle_lock();
		Buffer::Get().add_contents("You unlocked the door!\n\n");
	}

//******************************************************************************************************************************
// second_parsing()
//******************************************************************************************************************************

	void Action::second_parsing(std::string& object, std::string& target, const std::string& input){
		
		std::string word, target_temp; 
		std::unordered_set<std::string> stop_words = {"at", "to", "on", "in", "with", "towards", "up", "the"};
		//if we get: use "key on door", key is the object, door is the target
		//word is a variable we will use while extracting words from the string stream
		//target_temp will hold a candidate word for target while iterating through the stream.
		
		std::stringstream ss (input);
		//Now we get the second part of the input.
		//we have to be able to extract the right word into the target
		bool found_stop {false};
		while(ss >> word){
			//We pass stop words
			if(stop_words.find(word) != stop_words.end() && !found_stop){
				//If unordered_set.find() does not find anything it returns unordered_set.end();
				found_stop = true;
				continue;
			}
			//if target_temp is not empty it means object might be a composite word like "chesire cat" so we add a space
			if(!found_stop){
				
				if(!object.empty())
					object += " "; 
				object += word;
			}	
			if(found_stop){
				
				if(!target_temp.empty())
					target_temp += " "; 
				target_temp += word;
			}
		}
		target = target_temp;
	}

//******************************************************************************************************************************
// 
//******************************************************************************************************************************
