#include "move_object.h"

MoveObject::MoveObject(Vector2D pos, Dir dir) : 
	 direction(dir)
	, velocity(Vector2D(0,0))
	, m_bAlive(true)
{
	moveFrame = -1;
	angle = (270 + direction * 45) % 360;
	this->pos = pos;
}

MoveObject::~MoveObject()
{

}
