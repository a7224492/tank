#ifndef MYTANK_H
#define MYTANK_H

#include <SDL/SDL.h>
#include <vector>
#include "tank.h"

using namespace std;

class Bullet;
class SPoint;

class MyTank : public Tank
{
public:
	MyTank(int x, int y, Dir direction);
	virtual ~MyTank();
	void update();
	void draw(SDL_Surface *background);
	
	
	inline void changeToMoveState(){
		state = MOVE;
	};
	inline void changeToStandState(){
		state = STAND;
	};
	inline void changeToDestoryState(){
		state = DESTORY;
	}
	inline bool isMoveState() const{
		return state == MOVE;
	}
	inline bool isStandState() const{
		return state == STAND;
	}
	inline bool isDestoryState() const{
		return state == DESTORY;
	}
	
private:
	void excuteState();
	void worldTransformRect(SDL_Rect &rect);

	enum {
		MOVE,
		STAND,
		DESTORY
	}state;	
	struct{
		int x,y;
	}control;
	
	void shot();

};

#endif