#ifndef BULLET_H
#define BULLET_H

#include "move_object.h"

class Bullet : public MoveObject
{
public:
	Bullet(int x, int y, Dir direction);
	virtual ~Bullet();
	void changeStateToMove();
	inline void changeStateToDestory(){
		state = DESTORY;
	}
	inline bool checkDestory(){
		return state == DESTORY;
	}
	void update();
	void draw();
protected:
	enum {
		MOVE,
		DESTORY
	}state;
	bool isAlive;

	void excuteState();
	virtual void checkCollision() = 0;
};

#endif