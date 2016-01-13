#include "move.h"
#include "tank.h"
#include "bullet.h"
#include "bfield.h"

extern SDL_Surface *screen;
extern MyTank myTank;
extern Bfield bfield;
extern EnemyTank enemyTank[];

static BOOL isPointInRect(SDL_Rect *rect, int x, int y)
{
    if (!(rect->x > x || (rect->x+rect->w) < x || rect->y > x || (rect->y+rect->h)))
        return TRUE;
    return FALSE;
}

static BOOL isOverlapEnemyTank(MyTank *myTank)
{
    int i;
    for (i = 0; i < bfield.enemyTankAliveNum; ++i)
    {
        EnemyTank *enemy = &enemyTank[i];
        switch (myTank->dir)
        {
        case UP:
            if (isPointInRect(enemy->imgRect, myTank->x, myTank->y) || \
                    isPointInRect(enemy->imgRect, myTank->x+myTank->imgRect->w, myTank->y))
                return TRUE;
            break;
        case DOWN:
            if (isPointInRect(enemy->imgRect, myTank->x, myTank->y+myTank->imgRect->h) || \
                    isPointInRect(enemy->imgRect, myTank->x+myTank->imgRect->w, myTank->y+myTank->imgRect->h))
                return TRUE;
            break;
        case LEFT:
            if (isPointInRect(enemy->imgRect, myTank->x, myTank->y) || \
                    isPointInRect(enemy->imgRect, myTank->x, myTank->y+myTank->imgRect->h))
                return TRUE;
            break;
        case RIGHT:
            if (isPointInRect(enemy->imgRect, myTank->x+myTank->imgRect->w, myTank->y) || \
                    isPointInRect(enemy->imgRect, myTank->x+myTank->imgRect->w, myTank->y+myTank->imgRect->h))
                return TRUE;
            break;
        }
    }

    return FALSE;
}

void moveMyTank(int ms)
{
    switch (myTank.dir)
    {
    case UP:
        if ((myTank.y -= MY_TANK_SPEED*ms) < 0)
        {
            myTank.y = 0;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.y += MY_TANK_SPEED*ms;
        }

        break;
    case DOWN:
        if (((myTank.y +=MY_TANK_SPEED*ms)+MY_TANK_WIDTH) > screen->h)
        {
            myTank.y =screen->h-MY_TANK_WIDTH;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.y -= MY_TANK_SPEED*ms;
        }
        break;
    case LEFT:
        if ((myTank.x -= MY_TANK_SPEED*ms) < 0)
        {
            myTank.x = 0;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.x += MY_TANK_SPEED*ms;
        }
        break;
    case RIGHT:
        if (((myTank.x += MY_TANK_SPEED*ms)+MY_TANK_WIDTH) > screen->w)
        {
            myTank.x = screen->w-MY_TANK_HEIGHT;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.x -= MY_TANK_SPEED*ms;
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
