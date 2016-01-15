#ifndef BFIELD_H
#define BFIELD_H

#define TIME_PRODUCE_ENEMY 100

typedef struct Bfield
{
    int enemyTankAliveNum;
    int maxAliveEnemyNum;
    int remainEnemyNum;
    int *produceNextEnemyTime;
}Bfield;

void initBfield();
#endif // BFIELD_H

