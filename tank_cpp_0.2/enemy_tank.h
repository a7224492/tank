#ifndef ENEMY_TANK_H
#define ENEMY_TANK_H

#include "tank.h"

class EnemyTank : public Tank
{
public:
	EnemyTank(Vector2D pos, Dir dir);
	virtual ~EnemyTank();
	void update();
	void draw();

	inline void changeToMoveState(){
		state = MOVE;
	}
	inline void changeToDestoryState(){
		state = DESTORY;
	}
	inline void changeToStandState(){
		state = STAND;
	}
	inline bool isMoveState() const{
		return state == MOVE;
	}
	inline bool isDestoryState() const{
		return state == DESTORY;
	}
	inline bool isStandState() const{
		return state == STAND;
	}
private:
	enum {
		STAND,
		MOVE,
		DESTORY
	}state;
	int aiFrame;
	
	void executeState();
	void AI();
	void shot();
	void changeDirection(Dir direction);
};

#endif