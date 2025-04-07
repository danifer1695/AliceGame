#include "Utilities.h"
#include "Input_Parser.h"


//******************************************************************************************************************************
// extract_string()
//******************************************************************************************************************************

	std::string Utilities::extract_string(const std::string &data, const size_t &pos, const std::string &start_string, const std::string &end_string){
		
		//Used to read data from a file, extracts a string enclosed between a "start_string" and an "end_string", starting at pos
		//Example:	start_string: <Name>, end_string: </Name>,
		//			data: <Name>John Doe</Name>
		//			returns: John Doe
		
		//if given position to start parsing is beyond the total length of the string, we throw an error
		if(pos >= data.length())
			throw std::runtime_error("Position (" + std::to_string(pos) + ") out of range (" + std::to_string(data.length()) + ").");
		
		int start_string_len = start_string.length();
		
		size_t string_index_start = data.find(start_string, pos) + start_string_len;
		size_t string_index_end = data.find(end_string, pos);
		
		//Get length between the start and the end of the substring
		int len (string_index_end - string_index_start);
		
		return data.substr(string_index_start, len);
	}

//******************************************************************************************************************************
// extract_bool()
//******************************************************************************************************************************

	bool Utilities::extract_bool(const std::string &data, const size_t &pos, const std::string &start_string, const std::string &end_string){
		
		try{
			
			int to_bool = std::stoi(extract_string(data, pos, start_string, end_string));
			bool final_bool = (to_bool == 0) ? false : true;
			return final_bool;
			
		}catch(std::exception &ex){
			GAME_ERROR("This function only takes int booleans.");
		}
		return false;
	}

//******************************************************************************************************************************
// ifstream_to_string()
//******************************************************************************************************************************

	std::string Utilities::ifstream_to_string(std::ifstream &in_file){
		
		std::string to_return {};
		
		
		while(in_file){
			std::string section;
			std::getline(in_file, section);
			
			to_return.append(section);
		}
		
		return to_return;
			
	}

//******************************************************************************************************************************
// to_lower()
//******************************************************************************************************************************

	std::string Utilities::to_lower(const std::string &input){
		
		//we create a temp string
		std::string lower_case = input;
		//and turn all characters to lower case
		for (auto &c : lower_case) c = tolower(c);
		
		return lower_case;
	}
	
//******************************************************************************************************************************
// press_to_continue()
//******************************************************************************************************************************

	void Utilities::press_to_continue (){
		
		std::string input {};
		std::getline(std::cin, input);
		
		Input_Parser input_p(input);
		input_p.parse();
	}
	
//******************************************************************************************************************************
// random_binary()
//******************************************************************************************************************************

	double Utilities::random_binary (){
		
		std::srand(std::time(nullptr));  // Seed the RNG (only once in the program)
		int random_value = std::rand() % 2; // Generates 0 or 1

		return random_value;
	}