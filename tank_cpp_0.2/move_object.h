#ifndef MOVE_OBJECT_H
#define MOVE_OBJECT_H

#include <SDL/SDL.h>

class Game;

class MoveObject
{
public:
	enum Dir {UP=0,UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT}; 
	enum {
		DIR_NUM = 8
	};
	MoveObject(int x, int y, Dir dir);
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
protected:
	int x,y;
	struct{
		int x,y;
	}speed;
	
	SDL_Surface *imgs[DIR_NUM];
	SDL_Surface *screen;
	SDL_Rect oldRegion;
	Dir direction;
	int moveFrame;
	int angle;
	Game *game;
	const static int speedVectorX[DIR_NUM];
	const static int speedVectorY[DIR_NUM];
private:
	
};



#endif