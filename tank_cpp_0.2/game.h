#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <vector>

using namespace std;

class MyTank;
class EnemyTank;

class Game
{
public:
	Game(SDL_Surface *screen);
	int updateGame();
	void drawGame();
	void myTankChangeToDestory();
	void myTankDestory();
	void myBulletShotEnemy(int i);
	inline void enemyTankDestory(int i){
		delete enemyTankVec[i];
		enemyTankVec[i] = NULL;
	}
	inline void enemyTankDestory(EnemyTank *tank){
		for (int i = 0; i < enemyTankVec.size(); ++i)
		{
			if (enemyTankVec[i] == tank)
			{
				enemyTankDestory(i);
				break;
			}
		}
	}
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