#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
HANDLE Logger::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	
//******************************************************************************************************************************
// Destructor
//******************************************************************************************************************************
	
	Logger::~Logger(){
	}
	
//******************************************************************************************************************************
// CurrentDate
//******************************************************************************************************************************

	std::string Logger::CurrentDate(){
		
		std::time_t now {std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
		
		//We create a buffer string 30 characters long, filled with null characters, where the time will be stored
		std::string output (30, '\0');
		//strftime rectognizes %y, %m, etc and returns the relevant data
		std::strftime(&output[0], output.size(), "%y-%m-%d %H:%M:%S", std::localtime(&now));
		
		return output;
		
	}

//******************************************************************************************************************************
// Set_Color
//******************************************************************************************************************************

	//For windows only
	#ifdef _WIN32
	void Logger::Set_Color(Color color, HANDLE console_handle){
		
		switch (color){
			case Color::Red: SetConsoleTextAttribute(console_handle, 12); break;
			case Color::Green: SetConsoleTextAttribute(console_handle, 10); break;
			case Color::Yellow: SetConsoleTextAttribute(console_handle, 14); break;
			case Color::Blue: SetConsoleTextAttribute(console_handle, 9); break;
			default: SetConsoleTextAttribute(console_handle, 7); break; //default is white
		}
		
	}
	#endif

	void Logger::Set_Color(Color color){
		
		switch (color) {
			case Color::Red: std::cout << "\033[31m"; break;
			case Color::Green: std::cout << "\033[32m"; break;
			case Color::Yellow: std::cout << "\033[33m"; break;
			case Color::Blue: std::cout << "\033[34m"; break;
			default: std::cout << "\033[0m"; break; // Default is white
		}
		
	}

//******************************************************************************************************************************
// Reset_Color
//******************************************************************************************************************************

	#ifdef _WIN32
	void Logger::Reset_Color(HANDLE console_handle){
		
		SetConsoleTextAttribute(console_handle, 7); // Reset to white in selected console window
	}
	#endif

	void Logger::Reset_Color(){
		
		std::cout << "\033[0m";
		
	}

//******************************************************************************************************************************
// Print
//******************************************************************************************************************************


void Logger::Print(const std::string_view message, Color color){
	
	Set_Color(color);
	
	std::cout << message;
	
	Reset_Color();
}

//******************************************************************************************************************************
// Log
//******************************************************************************************************************************

void Logger::Log(const std::string message){
	
	Set_Color(GREEN);
	
	std::string to_print = CurrentDate() + " LOG: " + "- " + message + "\n";
	//std::cout << to_print;
	
	Input_Manager::Get().output_line(to_print);
	
	Reset_Color(hConsole);
	
}

//******************************************************************************************************************************
// Error
//******************************************************************************************************************************

void Logger::Error(const std::string_view message, std::source_location location){
	
	//Get a handle to the console window
	Set_Color(RED);
	
	std::string to_print {CurrentDate() + " ERROR:- " + std::string(message) + 
	" - FILE: " + location.file_name() + 
	" FUNC: " + location.function_name() + 
	" LINE: " + std::to_string(location.line()) + "\n"};
	
	//std::cout << to_print;
	
	//Now we write the message on the logs file
	Input_Manager::Get().output_line(to_print);
	
	
	Reset_Color();
	
}
//******************************************************************************************************************************
// New_Line
//******************************************************************************************************************************

	void Logger::New_Line(){
		
		std::cout << std::endl;
	
}