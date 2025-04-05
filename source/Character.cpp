#include "Character.h"


//******************************************************************************************************************************
// constructors()
//******************************************************************************************************************************
	
	Character::Character(const std::string &name, const std::string &description, const bool &is_enemy, const std::vector<std::string> dialogue_vec)
		:Interactable{name, description}, is_enemy{is_enemy}, dialogue_vec{dialogue_vec}{
			
			
		};
		
		
//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void Character::display() const{
		GAME_PRINT("This character's name is: " + get_name() + 
				". Description: " + description + 
				" Are they an enemy?: " + ((is_enemy) ? "True." : "False.") + "\n");
	}	
	
//******************************************************************************************************************************
// get_dialogue()
//******************************************************************************************************************************
	
	std::string Character::get_dialogue(){
		
		if(dialogue_vec.empty())
			throw std::runtime_error("get_dialogue vector in Character class empty.");
		
		GAME_LOG("Number of dialogue options in this character: " + std::to_string(dialogue_vec.size()) + " has_been_talked_to: " + std::to_string(has_been_talked_to));
		
		if(!has_been_talked_to) 
			return dialogue_database.at(dialogue_vec[0]);
		
		//if there is more than one dialogue, return second option when character has ben spoken to
		else if(dialogue_vec.size() > 1) 
			return dialogue_database.at(dialogue_vec[1]);
		
		else 
			return dialogue_database.at(dialogue_vec[0]);
		
	}
		
//******************************************************************************************************************************
// Operators
//******************************************************************************************************************************

	bool Character::operator==(const Character& rhs) const{
		
		return get_name() == rhs.get_name();
	}