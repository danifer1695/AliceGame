#ifndef LOGGER_H
#define LOGGER_H

#include <string_view>
#include <string>
#include <source_location>
#include <fstream>
#include "Input_Manager.h"

#ifdef _WIN32
	#include <windows.h>  // Windows-specific API
#endif

#define GAME_LOG(x) Logger::Log(x);
#define GAME_ERROR(x) Logger::Error(x);
#define GAME_PRINT(x) Logger::Print(x);
#define NEW_LINE Logger::New_Line();
#define SET_TEXT_COLOR(...) Logger::Set_Color(__VA_ARGS__);
#define RESET_TEXT_COLOR(x) Logger::Reset_Color(x);

#define WHITE Logger::Color::Default
#define RED Logger::Color::Red
#define GREEN Logger::Color::Green
#define YELLOW Logger::Color::Yellow
#define BLUE Logger::Color::Blue

class Logger{
	
private:

	// Windows console handle (only used in Windows)
	#ifdef _WIN32
	static HANDLE hConsole; //defined in the class source file
	#endif
	
	static std::string out_file_path;
	static std::string CurrentDate();
	
	static bool developer_mode {false};
	
public:

	enum class Color{
		Default,
		Red,
		Green,
		Yellow,
		Blue
	};
	
	Logger() {};
	~Logger();
	
	static void Set_Color(Color color);
	static void Reset_Color();
	static void Print(const std::string_view message, Color color = WHITE);
	static void Log(const std::string message);
	static void Error(const std::string_view message, std::source_location location = std::source_location::current());
	static void New_Line();
	
	//Windows-specific fucntions
	#ifdef _WIN32
	static void Set_Color(Color color, HANDLE console_handle);
	static void Reset_Color(HANDLE console_handle);
	#endif
};

#endif