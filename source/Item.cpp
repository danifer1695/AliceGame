#include "Item.h"

	
//******************************************************************************************************************************
// Constructors
//******************************************************************************************************************************
	
	Item::Item(const int &id_input, const std::string &name_input, const std::string &description_input, const std::string &display_input, const bool &can_store_input)
	:Interactable{name_input, description_input}, display_text{display_input}
	{
		id = id_input;
		can_store = can_store_input;
	}

	
//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void Item::display() const{
		std::string can_store_out = ((can_store == 0) ? "false" : "true");
		GAME_PRINT("Item ID:" + std::to_string(id) + ", name: " + get_name() + ", description: " + description + ", can store: " + can_store_out);
	}
	
//******************************************************************************************************************************
// Operators
//******************************************************************************************************************************

	bool Item::operator==(const Item& rhs) const{
		
		return id == rhs.get_id();
	}