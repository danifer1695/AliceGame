#ifndef COOR_STRUCT_
#define COOR_STRUCT_

//This class is vestigial and no longer has any practical use in the game, but I kept it because
//it could potentially be useful in the future should any mechanic need any Cardinal functionalities

	struct Coordinates{
		int x;
		int y;
		Coordinates(): x{0}, y{0}{};
		Coordinates(int x, int y): x{x}, y{y}{};
		Coordinates(const Coordinates &coor): x{coor.x}, y{coor.y}{};
		std::string display() const{return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";}
		
		friend Coordinates operator+(const Coordinates &lhs, const Coordinates &rhs){
			return Coordinates(lhs.x + rhs.x, lhs.y + rhs.y);
		}
	};


#endif