#include "Input_Parser.h"


//******************************************************************************************************************************
// Constructors()
//******************************************************************************************************************************

	Input_Parser::Input_Parser(std::string raw_input){
		
		get_words(raw_input);
	}
	
//******************************************************************************************************************************
// get_words()
//******************************************************************************************************************************
	
	void Input_Parser::get_words(std::string raw_input){
		
		GAME_LOG("Player entered: " + raw_input);
		
		std::string lower_case_input = TO_LOWER(raw_input);
		std::stringstream ss (lower_case_input);
		std::unordered_set<std::string> stop_words = {"at", "in", "the", "to", "with", "towards", "up"};
		std::string word, object_temp;
		
		//Extract first word into "verb"
		ss >> verb;
		
		//Now we get the second part of the input.
		//we have to be able to extract the right word into the object, so if the user entered
		// "look at room" we have to pass the stop word "at" and asign room as the objective
		bool found_stop {false};
		
		while(ss >> word){
			//We pass stop words
			if(stop_words.find(word) != stop_words.end() && !found_stop){
				//If unordered_set.find() does not find anything it returns unordered_set.end();
				found_stop = true;
				continue;
			}
			//if object_temp is not empty it means object might be a composite word like "chesire cat" so we add a space
			if(!object_temp.empty())
				object_temp += " "; 
			object_temp += word;
		}
		object = object_temp;
		
	}

//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void Input_Parser::display(){
		
		GAME_LOG("Verb: " + verb + ", Object: " + object);
	}

//******************************************************************************************************************************
// parse()
//******************************************************************************************************************************

	bool Input_Parser::parse(){
		
		//We return false if player selects to quit.
		
		if(verb == "go" || verb == "move" || verb == "enter"){
			Action::move_to(object);
			return true;
		}
		else if(verb == "inspect" || verb == "look" || verb == "investigate"){
			Action::inspect(object);
			return true;
		}
		else if(verb == "take" || verb == "get"){
			Action::take(object);
			return true;
		}
		else if(verb == "use" || verb == "throw"){
			Action::use(object);
			return true;
		}
		else if(verb == "talk" || verb == "speak"){
			Action::talk(object);
			return true;
		}
		else if(verb == "peek"){
			Action::peek(object);
			return true;
		}
		else if(verb == "drop" || verb == "remove"){
			Action::drop(object);
			return true;
		}
		else if(verb == "inventory"){
			Action::inspect("inventory");
			return true;
		}
		else if(verb == ""){
			Player::Get().get_current_room()->print();
			return true;
		}
		else if(verb == "wait"){
			Action::wait();
			return true;
		}
		else if(verb == "help"){
			Action::help();
			return true;
		}
		else if(verb == "q" || verb == "quit" || verb == "close"){
			Action::quit();
			return false;
		}
		else{
			Buffer::Get().add_contents("Sorry, I didn't get that!\nPlease try again.\n\n");
			Player::Get().get_current_room()->print();
			throw std::runtime_error("Command \"" + verb + "\" not recognized.");
		}
		
		return true;
	}