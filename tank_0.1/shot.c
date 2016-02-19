#include "shot.h"
#include "tank.h"
#include "bullet.h"

#define MY_TANK_SHOT_DELAY 180

extern MyTank myTank;

static int isMyTankAbleShot(MyTank *tank)
{
    if (tank->shotDelay != 0)
        return -1;
    int i;
    for (i = 0; i < MY_TANK_MAX_BULLET_NUM; ++i)
    {
        if (!tank->bullet[i])
        {
            return i;
        }
    }

    return -1;
}

void myTankShot()
{
    int i;

    if ((i = isMyTankAbleShot(&myTank)) != -1)
    {
        myTank.shotDelay = MY_TANK_SHOT_DELAY;
        myTank.bullet[i] = getBullet(myTank.shotx,myTank.shoty, myTank.dir);
    }
}
