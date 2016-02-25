#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <vector>
#include "Vector2D.h"

using namespace std;

class MyTank;
class EnemyTank;
class Tank;

class Game
{
public:
	Game(SDL_Surface *screen);
	int updateGame(double elapsedTime);
	void drawGame();
	
	inline int getEnemyTankNum(){
		return enemyTankVec.size();
	}
	inline const EnemyTank* getEnemyTank(int i){
		if (i >= enemyTankVec.size())
			return NULL;
		return enemyTankVec[i];
	}
	inline const MyTank* getMyTank(){
		return myTank;
	}
	inline SDL_Surface* getScreen() const {
		return screen;
	}
	inline void setElapsedTime(double elapsedTime){
		m_dElapsedTime = elapsedTime;
	}
	inline double getElapsedTime() const {
		return m_dElapsedTime;
	}

private:
	void loadData();
	void init();
	void drawFPS(SDL_Surface *screen, Vector2D pos);

	SDL_Surface *screen;
	SDL_Surface *background;

	MyTank *myTank;
	
	double m_dElapsedTime;

    vector<SDL_Surface *> myTankImg;
	vector<SDL_Surface *> bulletImgVec;
	vector<SDL_Surface *> enemyTankImgVec;
	vector<SDL_Surface *> bombImgVec;
	vector<EnemyTank *> enemyTankVec;
};

#endif
