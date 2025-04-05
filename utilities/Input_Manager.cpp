#include "Input_Manager.h"
#include "Logger.h"


//******************************************************************************************************************************
// Constructors()
//******************************************************************************************************************************
	
	Input_Manager::Input_Manager(){
	
		file_paths["items"] = "game_data/item_data.txt";
		file_paths["rooms"] = "game_data/map_data.txt";
		file_paths["characters"] = "game_data/character_data.txt";
		//GAME_LOG("Input Manager initialized!");
	}
	
//******************************************************************************************************************************
// Get_Instance()
//******************************************************************************************************************************
	
	Input_Manager& Input_Manager::Get(){
		
		static Input_Manager instance;
		
		return instance;
	}
	
//******************************************************************************************************************************
// get_raw_data()
//******************************************************************************************************************************
	
	std::string Input_Manager::get_raw_data(std::string key){
			
			//Check if key exists
			if(file_paths.find(key) == file_paths.end())
				throw std::runtime_error("Key " + key + " not found in file path database.");
			
			std::ifstream in_file (file_paths.at(key));
			std::string to_return {};
			std::string temp {};
			
			if(!in_file)
				throw std::runtime_error("File at " + file_paths.at(key) + " not found.");
			
			//Get data from file, line by line, then return it all as a string
			while(getline(in_file, temp)){
					
				to_return.append(temp);
			}
			
			return to_return;
		}
		
		
//******************************************************************************************************************************
// output_line()
//******************************************************************************************************************************
	
	void Input_Manager::output_line (std::string line){
			
			std::ofstream out_file;
			out_file.open(out_file_path, std::ios_base::app);
			
			out_file << line;
			
			out_file.close();
		}
