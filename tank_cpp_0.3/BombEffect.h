#ifndef BOMBEFFECT_H
#define BOMBEFFECT_H

#include "Vector2D.h"
#include <vector>
#include <SDL/SDL.h>

using namespace std;

class BombEffect
{
public:
	BombEffect();
	void update();
	void draw(SDL_Surface *screen);

	inline void setPos(Vector2D pos) {
		m_vPos = pos;
	}
	inline void addBombImg(SDL_Surface *img){
		m_vecBombImg.push_back(img);
	}
	inline bool getFinish() const {
		return m_bFinish;
	}
private:
	vector<SDL_Surface *> m_vecBombImg;
	Vector2D m_vPos;
	int m_iFrame;
	bool m_bFinish;
};

#endif 