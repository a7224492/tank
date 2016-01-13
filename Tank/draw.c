#include "draw.h"
#include "tank.h"
#include "bullet.h"
#include "move.h"

extern MyTank myTank;
extern SDL_Surface *screen;
extern SDL_Surface *background;

static void updateMyTank(int ms)
{
    if (myTank.isMove)
    {
        moveMyTank(ms);
    }
    if (myTank.shotDelay != 0)
    {
        if ((myTank.shotDelay -= ms) < 0)
        {
            myTank.shotDelay = 0;
        }
    }
    SDL_Rect rect = {myTank.x, myTank.y, MY_TANK_WIDTH, MY_TANK_HEIGHT};
    SDL_BlitSurface(myTank.img, myTank.imgRect, screen, &rect);
}

static void updateBackground()
{
    SDL_BlitSurface(background, NULL, screen, NULL);
}

static void updateBullet(int ms)
{
    int i;
    for (i = 0; i < MY_TANK_MAX_BULLET_NUM; ++i)
    {
        if (myTank.bullet[i])
        {
            Bullet *bullet = myTank.bullet[i];
            if (moveMyBullet(&myTank, i, ms))
            {
                SDL_Rect rect = {bullet->x, bullet->y, bullet->w, bullet->h};
                SDL_BlitSurface(bullet->img, bullet->imgRect, screen, &rect);
            }
        }
    }
}

void updateGame(int ms)
{
    /* must draw background firstly, or others are covered */
    updateBackground();
    updateMyTank(ms);
    updateBullet(ms);
}

void drawGame()
{
    SDL_Flip(screen);
}
