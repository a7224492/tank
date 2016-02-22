#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2D.h"
#include <SDL/SDL.h>

class Game;

class GameObject
{
public:
	inline Vector2D getPos() const{
		return this->pos;
	}
	inline void setPos(Vector2D pos){
		this->pos = pos;
	}
	
	inline void setScreen(SDL_Surface *screen){
		this->screen = screen;
	};
	inline void setGame(Game *game){
		this->game = game;
	}
	inline void setImg(SDL_Surface *img){
		m_pImg = img;
	}
protected:
	Vector2D pos;
	SDL_Surface *screen;
	SDL_Surface *m_pImg;
	Game *game;
};

#endif
