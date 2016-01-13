#ifndef TANK_H
#define TANK_H

#include <SDL/SDL.h>
#include "defs.h"

#define MY_TANK_WIDTH  44
#define MY_TANK_HEIGHT 33

#define MY_TANK_STEP_LEN 30
#define MY_TANK_SPEED  0.13

#define MY_TANK_MAX_BULLET_NUM 4
#define MY_TANK_SHOT_DELAY 180

struct Bullet;
typedef struct Bullet Bullet;

typedef struct _MyTank
{
    int x,y;
    int shotx,shoty;
    SDL_Surface *img;
    SDL_Rect *imgRect;
    DIR dir;
    int moveLen;
    BOOL isMove;
    Bullet *bullet[MY_TANK_MAX_BULLET_NUM];
    int shotDelay;
}MyTank;

void initMyTank(MyTank *mytank, int x, int y);
void setMyTankDir(MyTank *myTank, DIR dir);

#endif // TANK_H

