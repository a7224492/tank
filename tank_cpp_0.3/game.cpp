#include "game.h"
#include "mytank.h"
#include "utils.h"
#include "enemy_tank.h"
#include "ResourceManager.h"
#include <string>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>
#include <sstream>

using namespace std;

#ifndef _WIN32
#define IMG_PATH "/mnt/share/tank/gfx/"
#else 
#define IMG_PATH "E:/github_code/tank/gfx/"
#endif
#define MAX_ENEMY_NUM 1
#define BOMB_IMG_NUM 14

Game::Game(SDL_Surface *screen):
	screen(screen)
{
	loadData();
	resourceMgr->loadData();
	init();	
}

void Game::loadData()
{
	for (int i = 0; i < MoveObject::DIR_NUM; ++i)
	{
		string imgFile = IMG_PATH"TankImg"+itos(i)+".png";
		SDL_Surface *img = IMG_Load(imgFile.c_str());
		img = rotozoomSurface(img, 0, 0.6, SMOOTHING_ON);
		myTankImg.push_back(img);
	}
	for (int i = 0; i < MoveObject::DIR_NUM; ++i)
	{
		string imgFile = IMG_PATH"my_bullet_0"+itos(i)+".png";
		SDL_Surface *img = IMG_Load(imgFile.c_str());
		img = rotozoomSurface(img, 0, 0.3, SMOOTHING_ON);
		//SET_IMG_CANCEL_RGB(img, 255, 255, 255);
		bulletImgVec.push_back(img);
	}
	for (int i = 0; i < MoveObject::DIR_NUM; ++i)
	{
		string imgFile = IMG_PATH"EnemyTank0"+itos(i)+".png";
		SDL_Surface *img = IMG_Load(imgFile.c_str());
		img = rotozoomSurface(img, 0, 0.6, SMOOTHING_ON);
		//SET_IMG_CANCEL_RGB(img, 0, 0, 0);
		enemyTankImgVec.push_back(img);
	}
	for (int i = 0; i < BOMB_IMG_NUM; ++i)
	{
		string imgFile = IMG_PATH"bomb/"+itos(10000+BOMB_IMG_NUM-i)+".png";
		SDL_Surface *img = IMG_Load(imgFile.c_str());
		bombImgVec.push_back(rotozoomSurface(img, 0, 0.5, SMOOTHING_ON));
	}
	
	background = SDL_LoadBMP(IMG_PATH"arena.bmp");
}

void Game::init()
{
	myTank  = new MyTank(Vector2D(100,100), MoveObject::UP);
	myTank->setScreen(screen);
	myTank->setGame(this);
	myTank->setWidthHeight(58*0.6,62*0.6);
	for (int i = 0; i < MoveObject::DIR_NUM; ++i)
	{
		myTank->setDirImg(myTankImg[i], static_cast<MoveObject::Dir>(i));
		myTank->setBulletImg(bulletImgVec[i], static_cast<MoveObject::Dir>(i));
	}
	/************************************************************************/
	/* add bomb image                                                                     */
	/************************************************************************/
	for (int i = 0; i < bombImgVec.size(); ++i)
	{
		myTank->addBombImg(bombImgVec[i]);
	}

	for (int i = 0; i < MAX_ENEMY_NUM; ++i)
	{
		EnemyTank *enemy = new EnemyTank(Vector2D(50+100*i, 50), MoveObject::RIGHT);
		enemy->setScreen(screen);
		enemy->setGame(this);
		enemy->setWidthHeight(52*0.6,54*0.6);
		for (int j = 0; j < MoveObject::DIR_NUM; ++j)
		{
			enemy->setDirImg(enemyTankImgVec[j], static_cast<MoveObject::Dir>(j));
			enemy->setBulletImg(bulletImgVec[j], static_cast<MoveObject::Dir>(j));
		}
		for (int j = 0; j < bombImgVec.size(); ++j)
		{
			enemy->addBombImg(bombImgVec[j]);
		}
		enemyTankVec.push_back(enemy);
	}
}

int Game::updateGame(double elapsedTime)
{
	Uint8 *keystate = SDL_GetKeyState(0);
	if (keystate[SDLK_ESCAPE])
	{
		return -1;
	}
	if (myTank->getAlive())
	{
		myTank->update();
	}
	for (size_t i = 0; i < enemyTankVec.size(); ++i)
	{
		if (enemyTankVec[i]->getAlive())
			enemyTankVec[i]->update();
	}
	return 0;
}

void Game::drawGame()
{
	SDL_BlitSurface(background, NULL, screen, NULL);
	if (myTank->getAlive())
		myTank->draw();
	for (size_t i = 0 ; i < enemyTankVec.size(); ++i)
	{
		if (enemyTankVec[i]->getAlive())
		{
			enemyTankVec[i]->draw();
		}
	}
    drawFPS(screen, Vector2D(200,200));
	SDL_Flip(screen);
}
void Game::drawFPS(SDL_Surface *screen, Vector2D pos)
{
	double second = m_dElapsedTime/1000;

	double fps = 1/second;
    const TTF_Font *font = resourceMgr->getNormalFont();
	stringstream ss;

	ss << fps;
    SDL_Color clr = {255, 0, 0};
    SDL_Surface *fontSurface = TTF_RenderText_Solid(
			const_cast<TTF_Font *>(font), 
			ss.str().c_str(), 
			clr);
	SDL_Rect rect = {pos.x,pos.y,0,0};
	SDL_BlitSurface(fontSurface, NULL, screen, &rect);
}
