#ifndef MY_BULLET_H
#define MY_BULLET_H

#include "bullet.h"

class MyBullet : public Bullet
{
public:
	MyBullet(int x, int y, Dir direction);
	virtual ~MyBullet();
protected:
	virtual void checkCollision();
};

#endif