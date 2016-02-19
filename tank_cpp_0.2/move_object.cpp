#include "move_object.h"

const int MoveObject::speedVectorX[DIR_NUM] = {
	0,1,1,1,0,-1,-1,-1
};
const int MoveObject::speedVectorY[DIR_NUM] = {
	-1,-1,0,1,1,1,0,-1
};

MoveObject::MoveObject(int x, int y, Dir direction):
	x(x),
	y(y),
	direction(direction)
{
	oldRegion.x = 0;
	oldRegion.y = 0;
	oldRegion.w = 0;
	oldRegion.h = 0;
	speed.x = 0;
	speed.y = 0;
	moveFrame = -1;
	angle = (270+direction*45)%360;
}

MoveObject::~MoveObject()
{
}
