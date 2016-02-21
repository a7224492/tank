#ifndef MOVEOBJECTDIRECTION_H
#define MOVEOBJECTDIRECTION_H

#include "Vector2D.h"

class MoveObjectDirection
{
public:
	static inline MoveObjectDirection* getInstance();
	
	const Vector2D m_vUp        = { 0, -1 };
	const Vector2D m_vRightUp   = { 1, -1 };
	const Vector2D m_vRight     = { 1, 0 };
	const Vector2D m_vRightDown = { 1, 1 };
	const Vector2D m_vDown      = { 0, 1 };
	const Vector2D m_vLeftDown  = { -1, 1 };
	const Vector2D m_vLeft      = { -1, 0 };
	const Vector2D m_vleftUp    = { -1, -1 };
private:
	MoveObjectDirection(){};
	MoveObjectDirection(MoveObjectDirection &mod);
	MoveObjectDirection& operator=(const MoveObjectDirection &mod);
};

MoveObjectDirection* MoveObjectDirection::getInstance()
{
	static MoveObjectDirection mod;
	return &mod;
}

#define MoveDir MoveObject::getInstance()

#endif