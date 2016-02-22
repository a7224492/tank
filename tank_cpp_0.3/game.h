#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <vector>

using namespace std;

class MyTank;
class EnemyTank;
class Tank;

class Game
{
public:
	Game(SDL_Surface *screen);
	int updateGame();
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

private:
	void loadData();
	void init();

	SDL_Surface *screen;
	SDL_Surface *background;
	MyTank *myTank;
	vector<SDL_Surface *> myTankImg;
	vector<SDL_Surface *> bulletImgVec;
	vector<SDL_Surface *> enemyTankImgVec;
	vector<SDL_Surface *> bombImgVec;
	vector<EnemyTank *> enemyTankVec;
};

#endif