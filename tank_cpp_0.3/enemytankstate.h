#ifndef ENEMYTANKSTATE_H
#define ENEMYTANKSTATE_H

#include "State.h"

class EnemyTank;

namespace EnemyTankName {

class AttackState : public State<EnemyTank>
{
public:
    ~AttackState(){}
    AttackState* getInstance();

	virtual void Enter(EnemyTank *enemy);
	virtual void Execute(EnemyTank *enemy);
	virtual void Exit(EnemyTank *enemy);
private:
    AttackState(){}
	AttackState(const AttackState &);
	AttackState& operator= (const AttackState &);
};

}

#endif // ENEMYTANKSTATE_H

