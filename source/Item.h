#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "../utilities/Logger.h"
#include "Interactable.h"

class Item: public Interactable{
	
private:
	int id;
	bool can_store {false};
	std::string display_text {}; //for when items are dropped or not yet picked up.
	
public:
	Item() = default;
	Item(const int &id_input, const std::string &name_input, const std::string &description_input, const std::string &display_input, const bool &can_store_input);
	~Item() = default;
	
	//Member methods
	virtual void display() const override;
	
	//getters
	int get_id() const {return id;}
	bool get_store(){return can_store;}
	std::string get_display(){return display_text;}
	
	//Operators
	bool operator==(const Item& rhs) const;
};

#endif