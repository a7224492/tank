#include "move_object.h"

const int MoveObject::speedVectorX[DIR_NUM] = {
	0,1,1,1,0,-1,-1,-1
};
const int MoveObject::speedVectorY[DIR_NUM] = {
	-1,-1,0,1,1,1,0,-1
};

MoveObject::MoveObject(Vector2D pos, Dir dir) : 
	pos(pos)
	,direction(dir)
{
	speed.x = 0;
	speed.y = 0;
	moveFrame = -1;
	angle = (270 + direction * 45) % 360;
}

MoveObject::~MoveObject()
{

}
