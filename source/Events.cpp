#include "Events.h"
#include "Game.h"

	
//******************************************************************************************************************************
// Get()
//******************************************************************************************************************************
	Events& Events::Get(){
		static Events instance;
		return instance;
	}
	
//******************************************************************************************************************************
// game_intro
//******************************************************************************************************************************
	
	void Events::game_intro(){
		
		Buffer::Get().add_contents("Welcome to Alice's Breakout Adventure!\nAfter an unfortunate turn of events, Alice has found herself in the clutches of the Queen of Hearts' guards and locked away in a dreary cell, awaiting trial. In seven days' time, her fate shall be decided - so you must help her escape before it's too late. Best of luck!");
		
		Buffer::Get().add_contents("\n\nWould you like to read the game's instructions?\n(Yes/No):");
		Screen::Get().refresh();
		
		std::string response {};
		std::getline(std::cin, response);
		response = TO_LOWER(response);
		
		if(response == "yes" || response == "y"){
			help();
		}
		else{}
		
	}
	
//******************************************************************************************************************************
//get_caught()
//******************************************************************************************************************************
	
	void Events::get_caught(){
		
		Buffer::Get().add_contents("Guard: Oi! What are you doing here, you cheeky little devil! Go on then! Back to the cell with ye!");
		Buffer::Get().add_contents("\n\nYou are thrown back into your cell, and a day passes.\n\nPress enter to continue.");
		
		Screen::Get().refresh();
		std::cin.get();
		
		//Send player back to square one
		Player::Get().set_current_room(Map::Get().get_room_at_coor(Coordinates(0, 0)));
		Player::Get().set_current_day(Player::Get().get_current_day() + 1);
		
		if(Player::Get().get_current_day() >= Player::Get().get_max_days()){
				Events::Get().get_caught_game_over();
			}
		
	}
	
	
//******************************************************************************************************************************
//get_caught_game_over()
//******************************************************************************************************************************
	
	
	void Events::get_caught_game_over(){
		
		Buffer::Get().add_contents("And so, Alice was caught one too many times, and the day of her trial arrived at last. The Court was assembled, the Queen seated upon her grand throne, and all of Wonderland waited with bated breath.\nMay her Majesty show mercy on her.");
		Buffer::Get().add_contents("\n\nGAME OVER\n\nPress enter to exit the game.");
		
		Screen::Get().refresh();
		std::cin.get();
		
		throw 0;//Exception 0 breaks the game loop
		
	}
	
//******************************************************************************************************************************
//end_game()
//******************************************************************************************************************************
	
	void Events::end_game(){
		game->set_is_running(false);
		Buffer::Get().add_contents("You finally made it out of the castle. And so, as you run towards freedom, your adventure comes to a close.\n");
		Buffer::Get().add_contents("THE END\n\n");
		Buffer::Get().add_contents("Press enter to exit the game.");
		
		Screen::Get().refresh();
		ENTER_TO_CONTINUE;
	}
	
//******************************************************************************************************************************
//cheshire_first_encounter()
//******************************************************************************************************************************
	
	void Events::cheshire_first_encounter(){
		
		Buffer::Get().add_contents(dialogue_database.at("Cheshire_01"));
		Buffer::Get().add_contents("\n\nThe cat hands you a Club Key.\n\n");
		Buffer::Get().add_contents(dialogue_database.at("Cheshire_05"));
		
		if(!Player::Get().add_item_to_inventory("club key"))
			GAME_ERROR("Key item not found. Does its name match the one in the item_data list?")
		
	}
		
//******************************************************************************************************************************
//armory_distraction()
//******************************************************************************************************************************
	
	bool Events::armory_distraction(){
		
		//Player has to throw rock from the cell gallery
			if(TO_LOWER(Player::Get().get_current_room()->get_name()) == "armory"){
				
				//if you throw a rock from inside the armory you get caught
				Buffer::Get().add_contents("If you throw the rock from this close up you will not have time to escape the guards...\n\n");
				
				return false;
			}
			else if(TO_LOWER(Player::Get().get_current_room()->get_name()) != "cell gallery"){
				
				Buffer::Get().add_contents("You are too far away.\n\n");
				return false;
			}
			else{
				
				Buffer::Get().add_contents("You throw a rock into the armory and hit a shield hanging on the wall. It drops and crashes onto other items, starting a chaotic domino effect that echoes throughout the entire dungeon.\n\n");
				Buffer::Get().add_contents("Card Guard: What the bloody hell was that?\n\n");
				Buffer::Get().add_contents("You hear guards approaching from the Guard's Quarters, so you rush back into your cell.\n\n");
				
				Buffer::Get().add_contents("Press enter to continue.");
				
				Screen::Get().refresh();
				std::cin.get();
				
				Player::Get().set_current_room("Cell");
				Map::Get().get_room("Armory")->add_character("Card Guard");
				Map::Get().get_room("Guard's Quarters")->remove_character("Card Guard");
				
				return true;
			}
		
		
	}
		
//******************************************************************************************************************************
//armory_distraction()
//******************************************************************************************************************************
	
	void Events::random_character_spawn(const std::string& room){
		
		//Only run if none of the enemies have passed out
		bool enemy_passed {false};
		
		for(auto &character : Map::Get().get_room(room)->get_character_vec()){
			
			if(!character.get_is_conscious()) enemy_passed = true;
		}
		
		if(!enemy_passed){
			
			//Delete all existing enemies in the room
			Map::Get().get_room(room)->remove_all_enemies();
			
			//Roll a binary dice and decide if an enemy spawns
			if(RANDOM_BINARY == 1){
				GAME_LOG("Enemy spawned at " + room)
				Map::Get().get_room(room)->add_character("Card Guard");
			}
			
			for(auto &character : Map::Get().get_room(room)->get_character_vec()){
				
				//set is conscious to false if room contains beverage and character is an enemy
				
				if(Map::Get().get_room(room)->contains_item("beverage") && character.get_is_enemy()){
					GAME_LOG("Guard passed out!");
					character.set_is_conscious(false);
					
					Map::Get().get_room("Staff Hallway")->remove_item("Beverage");
					Map::Get().get_room("Staff Hallway")->add_item("Card Guard Spear");
				} 
			}
		}
	}
	
//******************************************************************************************************************************
//get_diamond_key()
//******************************************************************************************************************************
	
	void Events::get_diamond_key(){
		
		Buffer::Get().add_contents("You reach out with the Guard Spear and grab the key chain. One specific key among them grabs your attention, so you take it and leave the rest.\n");
		Buffer::Get().add_contents("You obtained the Diamond Key.\n\n");
		Buffer::Get().add_contents("Press enter to continue.");
		
		Player::Get().add_item_to_inventory("Diamond Key");
		
		Screen::Get().refresh();
		ENTER_TO_CONTINUE;
	}
	
//******************************************************************************************************************************
//dark_room_transform()
//******************************************************************************************************************************
	
	void Events::dark_room_transform(){
		
		Buffer::Get().add_contents("As you light the oil lamp, a warm glow spreads through the room, chasing away the shadows and revealing what had been hidden in the dark.\n\n");
		Buffer::Get().add_contents("Press enter to continue.");
		
		Screen::Get().refresh();
		std::cin.get();
		
		Player::Get().get_current_room()->transform_room(
			"Linen Room",
			"a rather stuffy little room, filled with stacked old curtains and table cloths, great dusty covers for furniture, and rows of servant uniforms, all pressed and ready to be worn. In a corner, a lonely wooden box sits collecting dust.",
			std::vector<Item>{ItemDatabase::Get().get_item_by_name("Servant Uniform"),
							  ItemDatabase::Get().get_item_by_name("Box"),
							  ItemDatabase::Get().get_item_by_name("Golden Coin")}
		);
		Player::Get().get_current_room()->set_has_been_visited(false);
	}
	
	
//******************************************************************************************************************************
//wear_uniform()
//******************************************************************************************************************************
	
	void Events::wear_uniform(){
		
		Buffer::Get().add_contents("You slip into the Servant Uniform. Now you'll blend in just like any other castle staff.\n\n");
		Buffer::Get().add_contents("Press enter to continue.");
		
		Player::Get().set_disguised(true);
		
		Screen::Get().refresh();
		ENTER_TO_CONTINUE;
	}
	
	
//******************************************************************************************************************************
//unlock_armory()
//******************************************************************************************************************************
	
	void Events::unlock_armory(){
		
		Map::Get().get_room("Guard's Quarters")->add_character("Card Guard");
		Map::Get().get_room("Armory")->remove_character("Card Guard");
		
		try{
			
			Map::Get().get_room("Armory")->get_door("Staff Hall").toggle_lock();
			
		}catch(std::exception &ex){
			GAME_ERROR(ex.what());
		}
		
	}
	
//******************************************************************************************************************************
//talk_to_cheshire()
//******************************************************************************************************************************
	
	void Events::talk_to_cheshire(){
		
		Character* cheshire = &Player::Get().get_current_room()->get_character_by_name("Cheshire Cat");
		
		//if the cat has not been talked to
		if(!cheshire->get_talked_to()){
			
			Events::Get().cheshire_first_encounter();
			cheshire->set_talked_to(true);
			Player::Get().set_treasure_quest_started(true);
			
		}
		//if the player has in fact talked to him before
		else{
			
			//if player has treasure in them, if they dont...
			bool treasure_found {false};
			
			std::shared_ptr<std::vector<Item>> inventory = Player::Get().get_inventory();
				
			//We remove treasure items from inventory
			//Using reverse iterator to safely erase while iterating
			for (auto it = inventory->rbegin(); it != inventory->rend(); ) {
				
				if (it->contains_name("item_treasure")) {
					
					Buffer::Get().add_contents("You gift the Cheshire Cat your " + it->get_name() + ".\n\n");
					
					treasure_found = true;
					
					Player::Get().add_treasure_collected();
					it = std::vector<Item>::reverse_iterator(inventory->erase(std::next(it).base()));
				} 
				else ++it;
			}
			
			//if player carries treasure and it meets the final number
			if(treasure_found && Player::Get().get_remaining_treasure() == 0){
				
				Buffer::Get().add_contents(dialogue_database.at("Cheshire_04"));
				Buffer::Get().add_contents("\n\nThe cat hands you a Heart Key.");
				if(!Player::Get().add_item_to_inventory("heart key"))
					GAME_ERROR("Key item not found. Does its name match the one in the item_data list?");
				Player::Get().set_treasure_completed(true);
				
			}
			//if player carries treasure but there are still some to be found
			else if(treasure_found && Player::Get().get_remaining_treasure() != 0){
				
				Buffer::Get().add_contents(dialogue_database.at("Cheshire_03"));
				Buffer::Get().add_contents("\n\nJust " + std::to_string(Player::Get().get_remaining_treasure()) + " more treasures for the grand price!");
				
			}
			//if player has completed the quest
			else if(Player::Get().get_treasure_completed()){
				
				Buffer::Get().add_contents("Cheshire Cat: Well donne! Now off you go!");
				
			}
			//if the player carries no treasure
			else{
				
				Buffer::Get().add_contents(dialogue_database.at("Cheshire_02"));
				Buffer::Get().add_contents("\n\nJust " + std::to_string(Player::Get().get_remaining_treasure()) + " more treasures for the grand price!");
			}
		}
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		ENTER_TO_CONTINUE;
	}
	
	
//******************************************************************************************************************************
//talk_to_fox()
//******************************************************************************************************************************
	
	void Events::talk_to_fox(){
		
		Character* fox = &Player::Get().get_current_room()->get_character_by_name("Cunning Fox");
		
		//if the cat has not been talked to
		if(!fox->get_talked_to()){
			
			Buffer::Get().add_contents(dialogue_database.at("Fox_01"));
			fox->set_talked_to(true);
			Player::Get().set_sweets_quest_started(true);
			
		}
		//if the player has in fact talked to him before
		else{
			
			//if player has sweets in them, if they dont...
			bool sweets_found {false};
			
			std::shared_ptr<std::vector<Item>> inventory = Player::Get().get_inventory();
				
			//We remove sweets items from inventory
			//Using reverse iterator to safely erase while iterating
			for (auto it = inventory->rbegin(); it != inventory->rend(); ) {
				
				if (it->contains_name("item_sweet")) {
					
					Buffer::Get().add_contents("You give the Cunning Fox your " + it->get_name() + ".\n\n");
					
					sweets_found = true;
					
					Player::Get().add_sweets_collected();
					it = std::vector<Item>::reverse_iterator(inventory->erase(std::next(it).base()));
				} 
				else ++it;
			}
			
			//if player carries sweets and it meets the required number
			if(sweets_found && Player::Get().get_remaining_sweets() == 0){
				
				Buffer::Get().add_contents(dialogue_database.at("Fox_04"));
				Buffer::Get().add_contents("\n\nThe fox hands you a Ruby Ring.");
				if(!Player::Get().add_item_to_inventory("Ruby Ring"))
					GAME_ERROR("Ruby Ring item not found. Does its name match the one in the item_data list?");
				Player::Get().set_sweets_completed(true);
				
			}
			//if player has completed the quest
			else if(Player::Get().get_sweets_completed()){
				
				Buffer::Get().add_contents("Fox: Really appreciate your help little girl heh heh.");
				
			}
			//if player carries sweets but there are still some to be found
			else if(sweets_found && Player::Get().get_remaining_sweets() != 0){
				
				Buffer::Get().add_contents(dialogue_database.at("Fox_03"));
				Buffer::Get().add_contents("\nJust " + std::to_string(Player::Get().get_remaining_sweets()) + " more sweet and the price is yours heh heh.");
				
			}
			//if the player carries no sweets
			else{
				
				Buffer::Get().add_contents(dialogue_database.at("Fox_02"));
				Buffer::Get().add_contents("\nJust " + std::to_string(Player::Get().get_remaining_sweets()) + " lil treats is all I ask for heh heh.");
			}
		}
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		ENTER_TO_CONTINUE;
	}
	
//******************************************************************************************************************************
// guard_permit_check()
//******************************************************************************************************************************
	
	bool Events::guard_permit_check(){
		
		if(Player::Get().contains_item_in_inventory("Break Permit")){
			
			Buffer::Get().add_contents(dialogue_database.at("Guard_04"));
			Buffer::Get().add_contents("\n\nPress enter to continue.");
			
			Screen::Get().refresh();
			std::cin.get();
				
			return true;
			
		}else{
			
			Buffer::Get().add_contents(dialogue_database.at("Guard_03"));
			Buffer::Get().add_contents("\n\nPress enter to continue.");
			
			Screen::Get().refresh();
			std::cin.get();
			return false;
		}
	}
	
//******************************************************************************************************************************
// choose_door()
//******************************************************************************************************************************
	
	Door* Events::choose_door(){
		
		Buffer::Get().add_contents("Which door?\n\n");
		
		std::vector<Door>* door_vec = &Player::Get().get_current_room()->get_door_vec();
		
		for(auto door : *door_vec){
			Buffer::Get().add_contents("-" + door.get_points_to() + "\n");
		}
		
		Screen::Get().refresh();
		
		std::string response {};
		std::getline(std::cin, response);
		
		for(auto& door : *door_vec){
			if(TO_LOWER(door.get_points_to()) == TO_LOWER(response)){
				Door* ptr = &door;
				return ptr;
			}
		}
		
		GAME_ERROR("Door to " + response + " not found.");
		throw std::runtime_error("Door to " + response + " not found.");
	}
	
	
//******************************************************************************************************************************
// help()
//******************************************************************************************************************************
	
	void Events::help(){
		
		Buffer::Get().add_contents("~~~~~~~~~~ HELP MENU (1 / 6) ~~~~~~~~~~");
		Buffer::Get().add_contents("\nIn this game you will take control of Alice and guide her out of the Queen of Hearts' Castle Prison. To achieve that you will talk to characters, use tools and interact with the environment. Interactable characters and items will often be listed for you in the game screen as such:\n");
		Buffer::Get().add_contents("\"There's a rock on the ground.\"\n");
		Buffer::Get().add_contents("\"These Characters are present: Cheshire Cat\"\n");
		Buffer::Get().add_contents("But this will not necessarily be always the case. Some interactable objects will only be implied by the description of the environment around you, so you are invited to use your imagination and try different things out!");
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		std::cin.get();
		
		Buffer::Get().add_contents("~~~~~~~~~~ HELP MENU (2 / 6) ~~~~~~~~~~");
		Buffer::Get().add_contents("\nThe way you will interact with the world is through written commands. The game does not differentiate between upper and lower cases, so there is no need to worry about matching the casing of the object you want to interact with. Here is a list of the main commands available to you:");
		Buffer::Get().add_contents("\n\n-\"Go to\" + Room name: This will move Alice from your current position to any of its connecting rooms.");
		Buffer::Get().add_contents("\n-\"Inspect\" + Object: This command will display a more detailed description of any item, character or room. To get a better picture of your surroundings, type \"inspect room\".");
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		std::cin.get();
		
		Buffer::Get().add_contents("~~~~~~~~~~ HELP MENU (3 / 6) ~~~~~~~~~~");
		Buffer::Get().add_contents("\n-\"Peek\" + Room name: Sometimes you might want to get an idea of what the room ahead of you looks like before you actually step inside to avoid any potential danger. The \"Peek\" command will let you do just that. It will give you a description of the room ahead of you, along with a list of any characters present - but it will not tell you what objects lie inside.");
		Buffer::Get().add_contents("\n-\"Use\" + Object: Utilize this command to make use of any of the items in your inventory. Sometimes, the command will require a target like such: \"use Club Key on Cell Gallery\".");
		Buffer::Get().add_contents("\n-\"Take\" + Object: This command will let you take an object from the environment and add it to your inventory.");
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		std::cin.get();
		
		Buffer::Get().add_contents("~~~~~~~~~~ HELP MENU (4 / 6) ~~~~~~~~~~");
		Buffer::Get().add_contents("\n-\"Drop\" + Object: Use this command if you wish to drop an object from your inventory onto the environment.");
		Buffer::Get().add_contents("\n-\"Inventory\": Type this command to see the contents of your inventory.");
		Buffer::Get().add_contents("\n-\"Help\": If you need a reminder of the game's functionalities, use this command to open this same help menu at any point during the game.");
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		std::cin.get();
		
		Buffer::Get().add_contents("~~~~~~~~~~ HELP MENU (5 / 6) ~~~~~~~~~~");
		Buffer::Get().add_contents("\n-\"Quit\": Enter this command if you wish to end the game. Please be mindful that there is no game saving function in this program, so should you want to play again you will have to start from the beginning!");
		Buffer::Get().add_contents("\n\nThese are not all the commands available for you to use in the game, so feel free to experiment!");
		Buffer::Get().add_contents("\nSomething else to note is that the game accepts a variety of words to refer to the same command or item. For example, entering \"Talk to Cheshire Cat\" and \"Speak to Cat\" will achieve the same thing.");
		
		Buffer::Get().add_contents("\n\nPress enter to continue.");
		Screen::Get().refresh();
		std::cin.get();
		
		Buffer::Get().add_contents("~~~~~~~~~~ HELP MENU (6 / 6) ~~~~~~~~~~");
		Buffer::Get().add_contents("\nFinally, if a command you are trying to use does not work, it probably means it is not included in the game's logic, so please try a different phrasing.");
		
		Buffer::Get().add_contents("\n\nThat's it! Have fun! Press enter to continue.");
		Screen::Get().refresh();
		std::cin.get();
	}
	
//******************************************************************************************************************************
// 
//******************************************************************************************************************************
	
	