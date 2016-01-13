#include "tank.h"
#include "bullet.h"

#define ENEMY_TANK_WIDTH 33
#define ENEMY_TANK_HEIGHT 44

extern SDL_Surface *myTankImg;
extern SDL_Surface *screen;
extern SDL_Surface *enemyTankImg;

static SDL_Rect myTankUpRect    = {0,  0,  MY_TANK_HEIGHT, MY_TANK_WIDTH};
static SDL_Rect myTankDownRect  = {MY_TANK_WIDTH, MY_TANK_HEIGHT, MY_TANK_HEIGHT, MY_TANK_WIDTH};
static SDL_Rect myTankLeftRect  = {0,  MY_TANK_WIDTH, MY_TANK_WIDTH, MY_TANK_HEIGHT};
static SDL_Rect myTankRightRect = {MY_TANK_HEIGHT, 0,  MY_TANK_WIDTH, MY_TANK_HEIGHT};
//static SDL_Rect myTankUpRightRect   = {78, 1,  52, 52};
//static SDL_Rect myTankDownLeftRect  = {78, 1,  52, 52};
//static SDL_Rect myTankUpLeftRect    = {78, 1,  52, 52};
//static SDL_Rect myTankDownRightRect = {78, 1,  52, 52};
static SDL_Rect enemyTankUpRect    = {0,  0,  ENEMY_TANK_WIDTH, ENEMY_TANK_HEIGHT};
static SDL_Rect enemyTankDownRect  = {ENEMY_TANK_HEIGHT,  ENEMY_TANK_WIDTH,  ENEMY_TANK_WIDTH, ENEMY_TANK_HEIGHT};
static SDL_Rect enemyTankLeftRect  = {0,  ENEMY_TANK_HEIGHT,  ENEMY_TANK_HEIGHT, ENEMY_TANK_WIDTH};
static SDL_Rect enemyTankRightRect = {ENEMY_TANK_WIDTH,  0,  ENEMY_TANK_HEIGHT, ENEMY_TANK_WIDTH};

static SDL_Rect enenmyTankUpRect = {0,0};

void initMyTank(MyTank *tank, int x, int y)
{
    int i;

    tank->img = myTankImg;
    tank->imgRect = &myTankUpRect;
    tank->x = x;
    tank->y = y;
    tank->w = MY_TANK_HEIGHT;
    tank->h = MY_TANK_WIDTH;
    setMyTankDir(tank, UP);
    tank->moveLen = 0;
    tank->isMove = FALSE;

    for (i = 0; i < MY_TANK_MAX_BULLET_NUM; ++i)
    {
        tank->bullet[i] = NULL;
    }

    tank->shotDelay = 0;
}

void setMyTankDir(MyTank *myTank, DIR dir)
{
    switch (dir)
    {
    case UP:
        myTank->imgRect = &myTankUpRect;
        myTank->shotx = myTank->x+13;
        myTank->shoty = myTank->y-8;
        break;
    case DOWN:
        myTank->imgRect = &myTankDownRect;
        myTank->shotx = myTank->x+12;
        myTank->shoty = myTank->y+42;
        break;
    case LEFT:
        myTank->imgRect = &myTankLeftRect;
        myTank->shotx = myTank->x-8;
        myTank->shoty = myTank->y+12;
        break;
    case RIGHT:
        myTank->imgRect = &myTankRightRect;
        myTank->shotx = myTank->x+42;
        myTank->shoty = myTank->y+13;
        break;
    }

    myTank->dir = dir;
}


void initEnemyTank(EnemyTank *enemyTank, int x, int y)
{
    enemyTank->x = x;
    enemyTank->y = y;
    enemyTank->w = ENEMY_TANK_WIDTH;
    enemyTank->h = ENEMY_TANK_HEIGHT;
    enemyTank->img = enemyTankImg;
    enemyTank->isAlive = TRUE;
    setEnemyTankDir(enemyTank, DOWN);
}

void setEnemyTankDir(EnemyTank *enemyTank, DIR dir)
{
    switch (dir)
    {
    case UP:
        enemyTank->imgRect = &enemyTankUpRect;
        break;
    case DOWN:
        enemyTank->imgRect = &enemyTankDownRect;
        break;
    case LEFT:
        enemyTank->imgRect = &enemyTankLeftRect;
        break;
    case RIGHT:
        enemyTank->imgRect = &enemyTankRightRect;
        break;
    }

    enemyTank->dir = dir;
}
