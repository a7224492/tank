#ifndef ENEMY_TANK_H
#define ENEMY_TANK_H

#include "tank.h"

class EnemyTank : public Tank
{
public:
	EnemyTank(Vector2D pos, Dir dir);
	virtual ~EnemyTank();

private:
	int aiFrame;
	
	void AI();
};

#endif