#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <sstream>

class Buffer{
	
private:

	Buffer(){};
	
	std::ostringstream contents {};
	
public:
	
	Buffer(const Buffer& buffer) = delete;
	Buffer& operator=(const Buffer&) = delete;
	
	static Buffer& Get();
	
	void add_contents(const std::string &input);
	std::string get_contents();
	void clear_buffer();
	
};

#endif