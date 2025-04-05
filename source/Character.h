#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <stdexcept>
#include "Interactable.h"
#include "DialogueDatabase.h"
#include "../utilities/Logger.h"

class Character: public Interactable{
	
private:

	bool is_enemy {false};
	bool has_been_talked_to {false};
	bool is_conscious {true};
	std::vector<std::string> dialogue_vec{};
public:

	Character(){};
	Character(const std::string &name, const std::string &description, const bool &is_enemy, const std::vector<std::string> dialogue_vec);
	
	//debugging
	virtual void display() const override;
	
	//getters
	bool get_is_enemy(){return is_enemy;}
	bool get_talked_to(){return has_been_talked_to;}
	bool get_is_conscious(){return is_conscious;}
	std::string get_dialogue();
	
	//setters
	void set_talked_to(bool set){has_been_talked_to = set;}
	void set_is_conscious(bool set){is_conscious = set;}
	
	//methods
	void add_to_dialogue_dict(std::string key, std::string value);
	
	//operators
	bool operator==(const Character& rhs) const;
};

#endif