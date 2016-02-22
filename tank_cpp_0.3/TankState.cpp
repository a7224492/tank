#include "TankState.h"
#include "tank.h"
#include "game.h"
#include "enemy_tank.h"
#include "mytank.h"

using namespace TankState;

GlobalState* GlobalState::getInstance()
{
	static GlobalState gs;
	return &gs;
}

void GlobalState::Execute(Tank *tank)
{
	
}

MoveState* MoveState::getInstance()
{
	static MoveState ms;
	return &ms;
}

void MoveState::Enter(Tank *tank)
{

}

void MoveState::Execute(Tank* tank)
{
	if (tank->getVelocity().isZero())
		tank->getFSM()->ChangeState(standState);

	tank->setVelocity(tank->getVelocity()*tank->getSpeed());
	tank->setAngle((270 + 45 * tank->getDirection()) % 360);
	tank->setPos(tank->getPos() + tank->getVelocity());

	if (tank->faceWall())
	{
		tank->setPos(tank->getPos() - tank->getVelocity());
		tank->getFSM()->ChangeState(TankState::standState);
	}
	if (tank->getType() == MY_TANK)
	{
		for (int i = 0; i < tank->getGame()->getEnemyTankNum(); ++i)
		{
			const EnemyTank *enemy = tank->getGame()->getEnemyTank(i);
			if (enemy->getAlive() && tank->faceOtherTank(enemy))
			{
				tank->setPos(tank->getPos() - tank->getVelocity());
				tank->getFSM()->ChangeState(TankState::standState);
			}
		}
	}
	if (tank->getType() == ENEMY_TANK)
	{
		const MyTank *myTank = tank->getGame()->getMyTank();
		if (myTank->getAlive() && tank->faceOtherTank(myTank))
		{
			tank->setPos(tank->getPos() - tank->getVelocity());
			tank->getFSM()->ChangeState(TankState::standState);
		}
	}
}

void MoveState::Exit(Tank* tank)
{

}

StandState* StandState::getInstance()
{
	static StandState ss;
	return &ss;
}

void StandState::Enter(Tank *tank)
{
	Vector2D velocity = tank->getVelocity();
	velocity.Zero();
	tank->setVelocity(velocity);
}

void StandState::Execute(Tank *tank)
{
	if (!tank->getVelocity().isZero())
	{
		tank->getFSM()->ChangeState(moveState);
	}
}

void StandState::Exit(Tank *Tank)
{
}

DestoryState* DestoryState::getInstance()
{
	static DestoryState ds;
	return &ds;
}

void DestoryState::Enter(Tank *tank)
{
	tank->getBombEffect()->setPos(tank->getPos());
}

void DestoryState::Execute(Tank *tank)
{
	tank->getBombEffect()->update();
	if (tank->getBombEffect()->getFinish())
	{
		tank->setAlive(false);
	}
}

void DestoryState::Exit(Tank *tank)
{

}

BulletReadyState* BulletReadyState::getInstance()
{
	static BulletReadyState brs;
	return &brs;
}

void BulletReadyState::Enter(Tank* tank)
{
	vector<Bullet *> &bulletVec = tank->getBulletVec();
	int i;

	for (i = 0; i < bulletVec.size(); ++i)
	{
		if (!bulletVec[i])
			break;
	}

	if (i == bulletVec.size())
	{
		tank->getShotFSM()->ChangeState(bulletRunOutState);
		return;
	}
	tank->setIsReadyShot(true);
}

void BulletReadyState::Execute(Tank* tank)
{
	if (!tank->getIsReadyShot())
	{
		tank->getShotFSM()->ChangeState(bulletDelayState);
	}
}

void BulletReadyState::Exit(Tank *tank)
{

}

BulletDelayState* BulletDelayState::getInstance()
{
	static BulletDelayState bds;
	return &bds;
}

void BulletDelayState::Enter(Tank *tank)
{
	
}

void BulletDelayState::Execute(Tank *tank)
{
	static int shotFrame = 0;

	shotFrame = (shotFrame + 1) % 200;
	if (shotFrame == 0)
	{
		tank->getShotFSM()->ChangeState(bulletReadyState);
	}
}

void BulletDelayState::Exit(Tank *tank)
{
	
}

BulletRunOutState* BulletRunOutState::getInstance()
{
	static BulletRunOutState bros;
	return &bros;
}

void BulletRunOutState::Enter(Tank *tank)
{

}

void BulletRunOutState::Execute(Tank *tank)
{
	vector<Bullet *> &bulletVec = tank->getBulletVec();
	int i;

	for (i = 0; i < bulletVec.size(); ++i)
	{
		if (!bulletVec[i])
			break;
	}
	if (i != bulletVec.size())
	{
		tank->getShotFSM()->ChangeState(bulletReadyState);
	}
}

void BulletRunOutState::Exit(Tank *tank)
{

}