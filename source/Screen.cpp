#include "Screen.h"


	
//******************************************************************************************************************************
// Get()
//******************************************************************************************************************************
	
	Screen& Screen::Get(){
		static Screen instance;
		return instance;
	}
	
//******************************************************************************************************************************
// refresh()
//******************************************************************************************************************************
	
	void Screen::refresh(){
		display();
		Buffer::Get().clear_buffer();
	}
	
//******************************************************************************************************************************
// print_info_panel()
//******************************************************************************************************************************

	void Screen::print_info_panel(){
		
		//null check
		std::shared_ptr<Room> room = Player::Get().get_current_room();
		std::string room_name = room ? room->get_name() : "???";
		
		std::string row1 (width, '=');
		std::cout 	<< row1 << std::endl;
		std::cout 	<< "= " << std::setw(23) << std::left << std::setfill(' ') << "Day: " + std::to_string(Player::Get().get_current_day()) <<
							  std::setw(23) << std::right << std::setfill(' ') << "Room: " + room_name << " =" << std::endl;
		std::cout 	<< row1 << std::endl;
	}
	
	
//******************************************************************************************************************************
// print_display_panel()
//******************************************************************************************************************************
	
	void Screen::print_display_panel(){
		
		std::string to_print = Buffer::Get().get_contents();
		
		std::string formatted_text = format_output(to_print);
		
		std::cout << formatted_text << std::endl;
	}
	
//******************************************************************************************************************************
// format_output()
//******************************************************************************************************************************
	std::string Screen::format_output(std::string to_print){
		
		int rows {20};
		int row_length = width + 1;
		
		//we create the empty buffer, filled with space ' ' characters
		std::string buffer (row_length * rows, ' ');
		
		//we add the \n at the end of each row
		for(int i = 0; i < buffer.length(); i++){
			
			//Insert \n characters at the end of every line (width + 1)
			if((i + 1) % row_length == 0){
				buffer[i] = '\n';
			}
		}
		
		for(int i = 0, j = 0 ; i < buffer.length() && j < to_print.length(); i++, j++){
			
			//if the input text has an \n we just skip to the next row by adding
			//the max width of the paragraph minus the modulus of i and (width + 1), to i
			if(to_print[j] == '\n'){
				i += (width - (i % row_length));
				continue;
			}
			
			//if first character in the line is a space, we skip it
			if(i % row_length == 0 && to_print[j] == ' '){
				
				j++;
			}
			
			//we scan for the end of the current word
			std::size_t word_end = to_print.find(' ', j);
			int until_next_space = word_end - j;
			//if the current character position "i" plus the characters until the next space add
			//up to more than or are equal to the row length, then we return false.
			bool word_fits = (((i + 1) % row_length) + until_next_space <= row_length); 
			
			//if the full word doesnt fit, we skip a line
			if(word_end != std::string::npos && !word_fits){
				i += (width - (i % row_length));
				if (j > 0) j--;
				continue;
			}
			
			//if the current character is a \n we skip it
			if(buffer[i] == '\n'){
				j--;
				continue;
			}
			//Check input string is not done printing
			else if(j < to_print.length())
				buffer[i] = to_print[j];
			
		}
		
		return buffer;
	}
//******************************************************************************************************************************
// print_menu()
//******************************************************************************************************************************

	void Screen::print_menu(){
		
		std::string row1 (width, '=');
		
		std::cout 	<< row1 << std::endl;
		
		//First line
		std::cout 	<< "=  " << std::setw(22) << std::right << std::setfill(' ') << "Que" <<
							  std::setw(22) << std::left << std::setfill(' ') << "sts" << "  =" << std::endl;
		//Second line
		std::cout 	<< "= " << std::setw(48) << std::right << std::setfill('~') << " =" << std::endl;
		
		//third line
		std::cout 	<< "=  " << std::setw(22) << std::left << std::setfill(' ') << Player::Get().get_treasure_ui() <<
							  std::setw(22) << std::right << std::setfill(' ') << Player::Get().get_sweets_ui() << "  =" << std::endl;
		
		std::cout 	<< row1 << std::endl;
	}
	
//******************************************************************************************************************************
// display()
//******************************************************************************************************************************

	void Screen::display(){
	
	std::cout << "\n\n";
	
	print_info_panel();
	print_display_panel();
	print_menu();
	}