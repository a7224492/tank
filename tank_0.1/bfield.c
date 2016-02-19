#include "bfield.h"
#include "tank.h"

#define MAX_ALIVE_ENENMY_NUM 3
#define INIT_REMAIN_ENEMY_NUM 10

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
    bfield.produceNextEnemyTime = (int *)malloc(sizeof(int)*bfield.maxAliveEnemyNum);
    for (i = 0; i < bfield.maxAliveEnemyNum; ++i)
    {
        bfield.produceNextEnemyTime[i] = -1;
    }
}



