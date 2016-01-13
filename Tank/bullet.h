#ifndef BULLET_H
#define BULLET_H

#include "defs.h"

typedef struct Bullet
{
    int x,y;
    int w,h;
    SDL_Surface  *img;
    SDL_Rect *imgRect;
    enum Dir dir;
    double speed;
}Bullet;

Bullet* getBullet(int x, int y, DIR dir);

#endif // BULLET_H

