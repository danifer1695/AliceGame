#include "CharacterDatabase.h"

//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	CharacterDatabase& CharacterDatabase::Get(){
		
		static CharacterDatabase instance;
		return instance;
	}
//******************************************************************************************************************************
// load_database()
//******************************************************************************************************************************
	
	void CharacterDatabase::load_database(){
		
		std::string data = Input_Manager::Get().get_raw_data("characters");
		
		std::vector<std::string> temp_string_vec = raw_data_string_to_object_data_string(data);
		
		//Now we have a vector with all the item data strings, we just have to create the objects using them
		
		for(std::string str : temp_string_vec){
			
			std::string name = EXTRACT_STRING(str, 0, "<Name>", "</Name>");
			std::string description = EXTRACT_STRING(str, 0, "<Description>", "</Description");
			bool is_enemy = EXTRACT_BOOL(str, 0, "<Is_Enemy>", "</Is_Enemy>");
			std::vector<std::string> dialogue_vec = fill_dialogue_vec(EXTRACT_STRING(str, 0, "<Dialogue>", "</Dialogue>"));
			
			character_vec.push_back(make_shared<Character>(name, description, is_enemy, dialogue_vec));
		}
	}
	
//******************************************************************************************************************************
// fill_dialogue_vec()
//******************************************************************************************************************************

	std::vector<std::string> CharacterDatabase::fill_dialogue_vec(const std::string &dialogue_list_raw){
		
		/*We create a string stream to parse through the raw string data and
		  separate the items from spaces and commas*/
		std::stringstream s_stream(dialogue_list_raw);
		std::string temp;
		std::vector<std::string> dialogue_names;//Here we will store the names of the items to then look up in the database
		
		while(std::getline(s_stream, temp, ',')){
			//Remove leading and trailing spaces
			size_t start = temp.find_first_not_of(" ");
			size_t end = temp.find_last_not_of(" ");
			
			if(start != std::string::npos && end != std::string::npos){
				dialogue_names.push_back(temp.substr(start, end - start + 1));
			}
		}
		
		return dialogue_names;
	}
	
//******************************************************************************************************************************
// raw_data_string_to_object_data_string()
//******************************************************************************************************************************
	
	std::vector<std::string> CharacterDatabase::raw_data_string_to_object_data_string(const std::string &data){
		
		std::vector<std::string> temp_string_vec{};
		//Index where search will start
		size_t index{0};
		size_t end{0};
		std::string temp {};
		
		while(end != std::string::npos && index < data.length()){
			std::string end_string = "</Character>";
			//we find the first end_string
			end = data.find(end_string, index);
			//we extract the item id
			temp = EXTRACT_STRING(data, index, "<Character>", end_string);
			
			//We update the search index
			index = end + end_string.length();
			temp_string_vec.push_back(temp);	
		};
		
		return temp_string_vec;
	}
	
//******************************************************************************************************************************
// get_character_by_name()
//******************************************************************************************************************************
	
	Character& CharacterDatabase::get_character_by_name(std::string name){
		
		//we turn both the input name and the item name to lower case to avoid discrepancies
		std::string lower_case_name = TO_LOWER(name);
		
		for(auto character : character_vec){
			
			if(character->contains_name(name)){
				return *character;
			}
		}
		throw std::runtime_error("Character " + name + " not found in Character Database");
	}

//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void CharacterDatabase::display(){
		
		for(auto &character : character_vec){
			character->display();
		}
	}