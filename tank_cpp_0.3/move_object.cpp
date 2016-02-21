#include "move_object.h"

const int MoveObject::speedVectorX[DIR_NUM] = {
	0,1,1,1,0,-1,-1,-1
};
const int MoveObject::speedVectorY[DIR_NUM] = {
	-1,-1,0,1,1,1,0,-1
};

MoveObject::MoveObject(Vector2D pos, Dir dir) : 
	pos(pos)
	, direction(dir)
	, velocity(Vector2D(0,0))
	, m_bAlive(true)
{
	moveFrame = -1;
	angle = (270 + direction * 45) % 360;
}

MoveObject::~MoveObject()
{

}
