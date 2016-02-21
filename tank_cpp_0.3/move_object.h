#ifndef MOVE_OBJECT_H
#define MOVE_OBJECT_H

#include <SDL/SDL.h>
#include "Vector2D.h"

class Game;

class MoveObject
{
public:
	enum Dir {UP = 0, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};
	enum {DIR_NUM = 8};
	MoveObject(Vector2D pos, Dir dir);
	virtual ~MoveObject();
	inline void setDirImg(SDL_Surface *img, Dir dir){
		imgs[dir] = img;
	}
	inline void setScreen(SDL_Surface *screen){
		this->screen = screen;
	};
	inline void setGame(Game *game){
		this->game = game;
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
	inline Vector2D getPos() const{
		return this->pos;
	}
	inline void setPos(Vector2D pos){
		this->pos = pos;
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
	Vector2D pos;
	Vector2D m_vHead;
	Vector2D m_vSide;
	Vector2D velocity;

	bool m_bAlive;
	
	double m_dSpeed;
	SDL_Surface *imgs[DIR_NUM];
	SDL_Surface *screen;
	SDL_Rect oldRegion;
	Dir direction;
	int moveFrame;
	double angle;
	Game *game;
	const static int speedVectorX[DIR_NUM];
	const static int speedVectorY[DIR_NUM];

private:
	
};

#endif