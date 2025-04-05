#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <stdexcept>
	
	class Logger;

	class Input_Manager{
		
	private:
		Input_Manager();
		//static Input_Manager instance is inside Get_Instance()
		
		std::unordered_map<std::string, std::string> file_paths;
		
		std::string out_file_path {"logs/logs.txt"};
		
	public:
		Input_Manager(const Input_Manager&) = delete; //we delete the copy constructor. We dont want any other copies of this class
		Input_Manager& operator=(const Input_Manager&) = delete; //we also delete the assignment operator.
		
		static Input_Manager& Get();
		std::string get_raw_data(std::string key);
		void output_line(std::string line);
	};

	
#endif