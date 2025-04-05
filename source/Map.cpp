#include "Map.h"


//******************************************************************************************************************************
// Constructor
//******************************************************************************************************************************
	
	Map::Map(){
		try{
			load_database();
			
		}catch(std::exception &ex){
			GAME_ERROR(ex.what());
		}
	}
	
//******************************************************************************************************************************
// Get()
//******************************************************************************************************************************
	
	Map& Map::Get(){
		
		static Map map;
		return map;
	}
		
//******************************************************************************************************************************
// load_database()
//******************************************************************************************************************************
	
	void Map::load_database(){
		
		std::string data = Input_Manager::Get().get_raw_data("rooms");
		
		//This returns a vector containing raw data for each of the rooms. so the file data will be cut and divided for 
		//each room
		std::vector<std::string> temp_string_vec = raw_data_string_to_object_data_string(data);
		
		//Now we have a vector with all the item data strings, we just have to create the objects using them
		
		for(std::string str : temp_string_vec){
			
			std::string name = EXTRACT_STRING(str, 0, "<Name>", "</Name>");
			std::string description = EXTRACT_STRING(str, 0, "<Description>", "</Description");
			std::vector<Coordinates> coordinates = extract_coordinates(EXTRACT_STRING(str, 0, "<Can_Store>", "</Can_Store>"));
			std::vector<Item> items_vec = fill_items_vec(EXTRACT_STRING(str, 0, "<Items>", "</Items>"));
			std::vector<Character> char_vec = fill_character_vec(EXTRACT_STRING(str, 0, "<Characters>", "</Characters>"));
			int is_final = std::stoi(EXTRACT_STRING(str, 0, "<Is_Final>", "</Is_Final>"));
			bool is_final_bool = (is_final == 0) ? false : true;
			std::vector<Door> door_vec = fill_door_vec(EXTRACT_STRING(str, 0, "<Door_List>", "</Door_List>"));
			
			//We construct the room object and push it into the room vector.
			room_vec.push_back(make_shared<Room>(name, description, coordinates, items_vec, char_vec, door_vec, is_final_bool));
		}
		
	}
	
//******************************************************************************************************************************
// raw_data_string_to_object_data_string()
//******************************************************************************************************************************
	
	std::vector<std::string> Map::raw_data_string_to_object_data_string(const std::string &data){
		
		std::vector<std::string> temp_string_vec;
		//Index where search will start
		size_t index{0};
		size_t end{0};
		std::string temp{};
		
		while(end != std::string::npos && index < data.length()){
			std::string end_string = "</Room>";
			//we find the first end_string
			end = data.find(end_string, index);
			//we extract the room data
			temp = EXTRACT_STRING(data, index, "<Room>", end_string);
			
			//We update the search index
			index = end + end_string.length();
			temp_string_vec.push_back(temp);	
		};
		
		return temp_string_vec;
	}
	
//******************************************************************************************************************************
// fill_items_vec()
//******************************************************************************************************************************

	std::vector<Item> Map::fill_items_vec(const std::string &item_list_raw){
		
		std::vector<Item> items_vec {};
		
		/*We create a string stream to parse through the raw string data and
		  separate the items from spaces and commas*/
		std::stringstream s_stream(item_list_raw);
		std::string temp;
		std::vector<std::string> item_names;//Here we will store the names of the items to then look up in the database
		
		while(std::getline(s_stream, temp, ',')){
			//Remove leading and trailing spaces
			size_t start = temp.find_first_not_of(" ");
			size_t end = temp.find_last_not_of(" ");
			
			if(start != std::string::npos && end != std::string::npos){
				item_names.push_back(temp.substr(start, end - start + 1));
			}
		}
		
		for(auto name : item_names){
			items_vec.push_back(ItemDatabase::Get().get_item_by_name(name));
		}
		
		return items_vec;
	}

	
//******************************************************************************************************************************
// fill_character_vec()
//******************************************************************************************************************************

	std::vector<Character> Map::fill_character_vec(const std::string &raw_data){
		
		std::vector<Character> character_vec {};
		
		/*We create a string stream to parse through the raw string data and
		  separate the items from spaces and commas*/
		std::stringstream s_stream(raw_data);
		std::string temp;
		std::vector<std::string> char_names;//Here we will store the names of the items to then look up in the database
		
		while(std::getline(s_stream, temp, ',')){
			//Remove leading and trailing spaces
			size_t start = temp.find_first_not_of(" ");
			size_t end = temp.find_last_not_of(" ");
			
			if(start != std::string::npos && end != std::string::npos){
				char_names.push_back(temp.substr(start, end - start + 1));
			}
		}
		
		for(auto name : char_names){
			character_vec.push_back(CharacterDatabase::Get().get_character_by_name(name));
		}
		
		return character_vec;
	}
	
//******************************************************************************************************************************
// fill_door_vec()
//******************************************************************************************************************************

	std::vector<Door> Map::fill_door_vec(const std::string &raw_data){
		
		//this creates a vector of Door objects created out of raw data, that is broken apart
		//and fed to each room constructor.
		
		std::vector<Door> temp_door_vec {};
		//Index where search will start
		size_t index{0};
		size_t end{0};
		std::string data{};
		std::string start_string = "<Door>";
		std::string end_string = "</Door>";
		
		
		//if we dont find start_string it means there are no doors so we just
		//return the empty temp_door_vec
		
		while(index < raw_data.length()){
			
			//we find the next </Door>
			end = raw_data.find(end_string, index);
			
			//Ensure we found a valid </Door>
			if(end == std::string::npos) break;
			
			//Extract the door raw_data
			data = EXTRACT_STRING(raw_data, index, start_string, end_string);
			
			//Update the search index
			index = end + end_string.length();
			
			//Push new door
			temp_door_vec.push_back(Door(data));	
			
			//Debugging number of loops
			//GAME_LOG("Count");
		};
		
		
		return temp_door_vec;
	}
	
//******************************************************************************************************************************
// extract_coordinates()
//******************************************************************************************************************************
	
	std::vector<Coordinates> Map::extract_coordinates(const std::string& input){
		
		std::vector<Coordinates> temp;
		std::regex pattern(R"(\((-?\d+),\s*(-?\d+)\))");
		std::smatch match;
		std::string str = input;
		
		while(std::regex_search(str, match, pattern)){
			int x = std::stoi(match[1].str());
			int y = std::stoi(match[2].str());
			temp.emplace_back(x, y);
			str = match.suffix();
		}
		
		return temp;
	}
	
//******************************************************************************************************************************
// display()
//******************************************************************************************************************************
	
	void Map::display(){
		
		for(auto room : room_vec){
			room->display();
			std::cout << std::endl;
		}
	}
	
//******************************************************************************************************************************
// get_room_at_coor()
//******************************************************************************************************************************

	std::shared_ptr<Room> Map::get_room_at_coor(Coordinates coor) const{
		
		for(auto room : room_vec){
			
			if(room->has_coordinates(coor))
				return room;
		}
		
		throw std::runtime_error("Room at " + coor.display() + " not found.");
	}	
	
//******************************************************************************************************************************
// get_room()
//******************************************************************************************************************************

	std::shared_ptr<Room> Map::get_room(const std::string &name){
		
		std::string name_lower = TO_LOWER(name);
		
		for(auto room : room_vec){
			
			if(TO_LOWER(room->get_name()) == name_lower)
				return room;
		}
		
		//we will catch this in Action::move_to()
		throw std::runtime_error("Room named " + name + " not found.");
	}
