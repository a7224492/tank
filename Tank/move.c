#include "move.h"
#include "tank.h"
#include "bullet.h"

extern SDL_Surface *screen;
extern MyTank myTank;

void moveMyTank(int ms)
{
    switch (myTank.dir)
    {
    case UP:
        if ((myTank.y -= MY_TANK_SPEED*ms) < 0)
        {
            myTank.y = 0;
        }

        break;
    case DOWN:
        if (((myTank.y +=MY_TANK_SPEED*ms)+MY_TANK_WIDTH) > screen->h)
        {
            myTank.y =screen->h-MY_TANK_WIDTH;
        }
        break;
    case LEFT:
        if ((myTank.x -= MY_TANK_SPEED*ms) < 0)
        {
            myTank.x = 0;
        }
        break;
    case RIGHT:
        if (((myTank.x += MY_TANK_SPEED*ms)+MY_TANK_WIDTH) > screen->w)
        {
            myTank.x = screen->w-MY_TANK_HEIGHT;
        }
        break;
    }

    myTank.moveLen = myTank.moveLen+MY_TANK_SPEED*ms;
    if (myTank.moveLen >= MY_TANK_STEP_LEN)
        myTank.isMove = FALSE;
}

BOOL moveMyBullet(MyTank *myTank, int i,int ms)
{
    Bullet *bullet = myTank->bullet[i];
    BOOL isAlive = TRUE;

    if (bullet)
    {
        switch (bullet->dir) {
        case UP:
            if (((bullet->y -= bullet->speed*ms)) <0)
            {
                bullet->y = 0;
                isAlive = FALSE;
            }
            break;
        case DOWN:
            if (((bullet->y += bullet->speed*ms)+bullet->w) > screen->h)
            {
                bullet->y = screen->h-bullet->w;
                isAlive = FALSE;
            }
            //bullet->y += 5;
            break;
        case LEFT:
            if (((bullet->x -= bullet->speed*ms)) < 0)
            {
                bullet->x = 0;
                isAlive = FALSE;
            }
            break;
        case RIGHT:
            if (((bullet->x += bullet->speed*ms)+bullet->w) > screen->w)
            {
                bullet->x = screen->w-bullet->w;
                isAlive = FALSE;
            }
            break;
        }
    }

    if (!isAlive)
    {
        free (myTank->bullet[i]);
        myTank->bullet[i] = NULL;
    }
    return isAlive;
}
