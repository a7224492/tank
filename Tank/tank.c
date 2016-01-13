#include "tank.h"
#include "bullet.h"

extern SDL_Surface *myTankImg;
extern SDL_Surface *screen;

static SDL_Rect myTankUpRect    = {0,  0,  MY_TANK_HEIGHT, MY_TANK_WIDTH};
static SDL_Rect myTankDownRect  = {MY_TANK_WIDTH, MY_TANK_HEIGHT, MY_TANK_HEIGHT, MY_TANK_WIDTH};
static SDL_Rect myTankLeftRect  = {0,  MY_TANK_WIDTH, MY_TANK_WIDTH, MY_TANK_HEIGHT};
static SDL_Rect myTankRightRect = {MY_TANK_HEIGHT, 0,  MY_TANK_WIDTH, MY_TANK_HEIGHT};
//static SDL_Rect myTankUpRightRect   = {78, 1,  52, 52};
//static SDL_Rect myTankDownLeftRect  = {78, 1,  52, 52};
//static SDL_Rect myTankUpLeftRect    = {78, 1,  52, 52};
//static SDL_Rect myTankDownRightRect = {78, 1,  52, 52};

void initMyTank(MyTank *tank, int x, int y)
{
    int i;

    tank->img = myTankImg;
    tank->imgRect = &myTankUpRect;
    tank->x = x;
    tank->y = y;
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
