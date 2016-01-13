#include "bfield.h"
#include "tank.h"

#define MAX_ALIVE_ENENMY_NUM 3

Bfield bfield;
MyTank myTank;
EnemyTank enemyTank[MAX_ALIVE_ENENMY_NUM];

void initBfield()
{
    int i;
    bfield.enemyTankAliveNum = 3;
    bfield.maxAliveEnemyNum  = MAX_ALIVE_ENENMY_NUM;
    initMyTank(&myTank, 400, 300);
    for (i = 0; i < 3; ++i)
    {
        initEnemyTank(&enemyTank[i], 100+100*i, 100);
    }
}



