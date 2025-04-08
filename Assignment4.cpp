//Documentation template from the GoodDocs file by Richard S. Huntrods
	
	/* 
	 Title: Assignment4.cpp
	 
	Description: The Queen of Hearts has caught up to Alice. She’s had enough of her, this time was 
		the time. The execution will go through. 
		Alice is in a cell in the castle’s dungeons awaiting her – loosely called- trial. Will she pose 
		any kind of resistance and find a way to escape? A sweet innocent girl, Alice is no superhero. 
		So, the player will have to use their wits rather than violence to help her out. 
		Added to that, the player does not have all the time in the world to find her way out of this 
		situation. If the day of the trial arrives and Alice is still inside the dungeon, she will be 
		taken away and face her ultimate fate. 
	 
	 Date: April 08 2025
	 
	 Author: Daniel Fernandez Martinez
	 
	 Version: 1.0
	*/

	/*
	 DOCUMENTATION
	 
	 Program Purpose:
		Text-based adventure game

	 Compile (Cygwin): make
	 Compile (MinGW): mingw32-make
	 
	 Execution (Cygwin): ./Assignment4.exe
	 Execution (MinGW): Assignment4.exe
	 
	 Notes: in Cygwin, main must return type int
	 
	 Bibliography:
	  
	 Classes: 

	*/


#include "source/Game.h"

int main(){
	
	Game game;
	game.Run();
	
	return 0;
	
}