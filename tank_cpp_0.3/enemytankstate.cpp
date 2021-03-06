#include "enemytankstate.h"
#include "Vector2D.h"
#include "mytank.h"
#include "game.h"
#include "enemy_tank.h"
#include "utils.h"

using namespace EnemyTankName;

AttackState* AttackState::getInstance()
{
	static AttackState es;
	return &es;
}

void AttackState::Enter(EnemyTank *enemy)
{
}

void AttackState::Execute(EnemyTank *enemy)
{
    const MyTank *tank = enemy->getGame()->getMyTank();
	Vector2D relativePos = enemy->getPos()-tank->getPos();
    double mostShortDist = MaxDouble;
    int index = -1;
	for (int i = 0; i < MoveObject::DIR_NUM; ++i){
        Vector2D tempDist = sinVector(relative, directionVelocity[i]);
        if (mostShortDist > tempDist.Length()){
            mostShortDist = tempDist.Length();
            index = i;
        }
	}

}

void AttackState::Exit(EnemyTank *enemy)
{
}
