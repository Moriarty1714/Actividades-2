#include <iostream>

enum class State { MENU, GAME, EXIT };

//Vec2 
class Vec2 {
public:
	int x;
	int y;

	Vec2() { x = 0; y = 0; }
}mousePos;

bool colPointToRect(int xPoint, int yPoint, int xRect, int yRect, int wRect, int hRect) {
	return xPoint < (xRect + wRect) && xPoint>xRect && yPoint  < (yRect + hRect) && yPoint > yRect;
}

