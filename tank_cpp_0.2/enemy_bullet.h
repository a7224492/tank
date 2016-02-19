#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(int x, int y, Dir dir);
	virtual ~EnemyBullet();
protected:
	virtual void checkCollision();
};

#endif