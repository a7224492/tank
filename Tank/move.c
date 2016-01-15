#include "move.h"
#include "tank.h"
#include "bullet.h"
#include "bfield.h"
#include <stdio.h>

extern SDL_Surface *screen;
extern MyTank myTank;
extern Bfield bfield;
extern EnemyTank enemyTank[];

static BOOL isPointInRect(SDL_Rect *rect, int x, int y)
{
    if (!(rect->x > x || (rect->x+rect->w) < x || rect->y > y || (rect->y+rect->h) < y))
    {
        return TRUE;
    }
    return FALSE;
}

static BOOL isOverlapEnemyTank(MyTank *myTank)
{
    int i;
    int p1x,p1y;
    int p2x,p2y;

    switch (myTank->dir)
    {
    case UP:
        p1x = myTank->x;
        p1y = myTank->y;
        p2x = myTank->x+myTank->imgRect->w;
        p2y = myTank->y;
        break;
    case DOWN:
        p1x = myTank->x;
        p1y = myTank->y+myTank->imgRect->h;
        p2x = myTank->x+myTank->imgRect->w;
        p2y = myTank->y+myTank->imgRect->h;
        break;
    case LEFT:
        p1x = myTank->x;
        p1y = myTank->y;
        p2x = myTank->x;
        p2y = myTank->y+myTank->imgRect->h;
        break;
    case RIGHT:
        p1x = myTank->x+myTank->imgRect->w;
        p1y = myTank->y;
        p2x = myTank->x+myTank->imgRect->w;
        p2y = myTank->y+myTank->imgRect->h;
        break;
    }

    for (i = 0; i < bfield.enemyTankAliveNum; ++i)
    {
        EnemyTank *enemy = &enemyTank[i];
        if (!enemy->isAlive)
            continue;
        SDL_Rect rect = {enemy->x, enemy->y, enemy->w, enemy->h};
        if (isPointInRect(&rect, p1x,p1y) || isPointInRect(&rect, p2x, p2y))
            return TRUE;
    }

    return FALSE;
}

void moveMyTank(int ms)
{
    int len = MY_TANK_SPEED*ms;
    switch (myTank.dir)
    {
    case UP:
        if ((myTank.y -= len) < 0)
        {
            myTank.y = 0;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.y += len;
        }

        break;
    case DOWN:
        if (((myTank.y += len)+myTank.imgRect->h) > screen->h)
        {
            myTank.y =screen->h-myTank.imgRect->h;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.y -= len;
        }
        break;
    case LEFT:
        if ((myTank.x -= len) < 0)
        {
            myTank.x = 0;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.x += len;
        }
        break;
    case RIGHT:
        if (((myTank.x += len)+myTank.imgRect->w) > screen->w)
        {
            myTank.x = screen->w-myTank.imgRect->w;
        }else if (isOverlapEnemyTank(&myTank))
        {
            myTank.x -= len;
        }
        break;
    }

    myTank.moveLen = myTank.moveLen+MY_TANK_SPEED*ms;
    if (myTank.moveLen >= MY_TANK_STEP_LEN)
        myTank.isMove = FALSE;
}

static int bulletHitEnemyTank(Bullet *bullet)
{
    int i;
    int p1x,p1y;
    int p2x,p2y;

    switch (bullet->dir)
    {
    case UP:
        p1x = bullet->x;
        p1y = bullet->y;
        p2x = bullet->x+bullet->imgRect->w;
        p2y = bullet->y;
        break;
    case DOWN:
        p1x = bullet->x;
        p1y = bullet->y+bullet->imgRect->h;
        p2x = bullet->x+bullet->imgRect->w;
        p2y = bullet->y+bullet->imgRect->h;
        break;
    case LEFT:
        p1x = bullet->x;
        p1y = bullet->y;
        p2x = bullet->x;
        p2y = bullet->y+bullet->imgRect->h;
        break;
    case RIGHT:
        p1x = bullet->x+bullet->imgRect->w;
        p1y = bullet->y;
        p2x = bullet->x+bullet->imgRect->w;
        p2y = bullet->y+bullet->imgRect->h;
        break;
    }
    for (i = 0; i < bfield.enemyTankAliveNum; ++i)
    {
        if (!enemyTank[i].isAlive)
            continue;
        SDL_Rect rect = {enemyTank[i].x, enemyTank[i].y, enemyTank[i].imgRect->w, enemyTank[i].imgRect->h};
        if (isPointInRect(&rect, p1x, p1y) || isPointInRect(&rect, p2x,p2y))
            return i;
    }

    return -1;
}

BOOL moveMyBullet(MyTank *myTank, int i,int ms)
{
    Bullet *bullet = myTank->bullet[i];
    BOOL isAlive = TRUE;
    int diedEnemyIndex;

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

    if ((diedEnemyIndex = bulletHitEnemyTank(bullet)) != -1)
    {
        enemyTank[diedEnemyIndex].isAlive = FALSE;
        isAlive = FALSE;
        bfield.produceNextEnemyTime[i] = TIME_PRODUCE_ENEMY;
    }

    if (!isAlive)
    {
        free (myTank->bullet[i]);
        myTank->bullet[i] = NULL;
    }
    return isAlive;
}
