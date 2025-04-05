/*

	To compile:
	
	mingw32-make
	
	g++ -std=c++20 Test01.cpp source\Events.cpp source\Door.cpp source\Action.cpp source\Buffer.cpp source\Game.cpp source\Player.cpp source\Room.cpp source\Character.cpp source\CharacterDatabase.cpp source\Screen.cpp source\Item.cpp source\ItemDatabase.cpp utilities\Input_Parser.cpp utilities\Logger.cpp utilities\Input_Manager.cpp utilities\Utilities.cpp source\Map.cpp -o test.exe
	
	Look into "MakeFile" as the compile command gets longer

*/

#include "source/Game.h"
//#include "source/Map.h"
//#include "utilities/Utilities.h"

int main(){
	
	Game game;
	game.Run();
	
	return 0;
	
}