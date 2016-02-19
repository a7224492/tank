#include "bullet.h"

#define BULLET_WIDTH  8
#define BULLET_HEIGHT 10
#define BULLET_SPEED 0.1789

extern SDL_Surface *bulletImg;

static SDL_Rect upRect = {0,0,BULLET_WIDTH,BULLET_HEIGHT};
static SDL_Rect downRect = {0,BULLET_HEIGHT,BULLET_WIDTH,BULLET_HEIGHT};
static SDL_Rect leftRect = {BULLET_WIDTH,BULLET_WIDTH,BULLET_HEIGHT,BULLET_WIDTH};
static SDL_Rect rightRect = {BULLET_WIDTH,0,BULLET_HEIGHT,BULLET_WIDTH};

Bullet* getBullet(int x, int y, DIR dir)
{
    Bullet *bullet;

    bullet = (Bullet *)malloc(sizeof(Bullet));
    bullet->x = x;
    bullet->y = y;
    bullet->dir = dir;

    bullet->img = bulletImg;
    bullet->w = BULLET_WIDTH;
    bullet->h = BULLET_HEIGHT;

    switch (dir)
    {
    case UP:
        bullet->imgRect = &upRect;
        break;
    case DOWN:
        bullet->imgRect = &downRect;
        break;
    case LEFT:
        bullet->imgRect = &leftRect;
        break;
    case RIGHT:
        bullet->imgRect = &rightRect;
        break;
    }

    bullet->speed = BULLET_SPEED;

    return bullet;
}
