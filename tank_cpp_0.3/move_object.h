#ifndef MOVE_OBJECT_H
#define MOVE_OBJECT_H

#include <SDL/SDL.h>
#include <iostream>
#include "Vector2D.h"
#include "GameObject.h"
#include <map>

class Game;

class MoveObject : public GameObject
{
public:
	enum Dir {UP = 0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};
	enum {DIR_NUM = 8};

	MoveObject(Vector2D pos, Dir dir);
	virtual ~MoveObject();
	
	inline void setDirImg(SDL_Surface *img, Dir dir){
		imgs[dir] = img;
	}
	inline double getAngle() const{
		return this->angle;
	}
	inline void setAngle(double angle){
		this->angle = angle;
	}
	inline void setVelocity(Vector2D velocity){
		this->velocity = velocity;
	}
	inline Vector2D getVelocity() const{
		return this->velocity;
	}
	inline double getSpeed() const {
		return this->m_dSpeed;
	}
	inline Dir getDirection() const {
		return this->direction;
	}
	
	inline Game* getGame() const {
		return game;
	}
	inline bool getAlive() const {
		return this->m_bAlive;
	}
	inline void setAlive(bool alive) {
		m_bAlive = alive;
	}
	
protected:
	Vector2D m_vHead;
	Vector2D m_vSide;
	Vector2D velocity;

	bool m_bAlive;
	
	double m_dSpeed;
	SDL_Surface *imgs[DIR_NUM];
	
	SDL_Rect oldRegion;
	Dir direction;
	int moveFrame;
	double angle;
	
private:
	
};

const Vector2D directionVelocity[] = {
    Vector2D(0,-1),
    Vec2DNormalize(Vector2D(1,-1)),
    Vector2D(1,0),
    Vec2DNormalize(Vector2D(1,1)),
    Vector2D(0,1),
    Vec2DNormalize(Vector2D(-1,1)),
    Vector2D(-1,0),
    Vec2DNormalize(Vector2D(-1,-1))
};

MoveObject::Dir getDirByVelocity(Vector2D velocity)
{
    for (int i = 0; i < MoveObject::DIR_NUM; ++i) {
        if (velocity == directionVelocity[i])
            return static_cast<MoveObject::Dir>(i);
    }
}


#endif
