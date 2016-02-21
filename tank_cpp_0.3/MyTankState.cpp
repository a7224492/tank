#include "MyTankState.h"
#include "mytank.h"
#include "enemy_tank.h"
#include "game.h"
#include "bullet.h"


//MoveState* MoveState::getInstance()
//{
//	static MoveState ms;
//	return &ms;
//}
//
//void MoveState::Enter(MyTank *tank)
//{
//	
//}
//
//void MoveState::Execute(MyTank* tank)
//{
//	if (tank->getVelocity().isZero())
//		tank->getFSM()->ChangeState(myTankStandState);
//
//	tank->setVelocity(tank->getVelocity()*tank->getSpeed());
//	tank->setAngle((270 + 45 * tank->getDirection()) % 360);
//	tank->setPos(tank->getPos() + tank->getVelocity());
//
//	if (tank->faceWall())
//	{
//		tank->setPos(tank->getPos() - tank->getVelocity());
//	}
//	for (int i = 0; i < tank->getGame()->getEnemyTankNum(); ++i)
//	{
//		const EnemyTank *enemy = tank->getGame()->getEnemyTank(i);
//		if (enemy && tank->faceOtherTank(enemy))
//		{
//			tank->setPos(tank->getPos() - tank->getVelocity());
//		}
//	}
//}
//
//void MoveState::Exit(MyTank* tank)
//{
//
//}
//
//StandState* StandState::getInstance()
//{
//	static StandState ss;
//	return &ss;
//}
//
//void StandState::Enter(MyTank *tank)
//{
//	Vector2D velocity = tank->getVelocity();
//	velocity.Zero();
//	tank->setVelocity(velocity);
//}
//
//void StandState::Execute(MyTank *tank)
//{
//	if (!tank->getVelocity().isZero())
//	{
//		tank->getFSM()->ChangeState(myTankMoveState);
//	}
//}
//
//void StandState::Exit(MyTank *Tank)
//{
//}
//
//DestoryState* DestoryState::getInstance()
//{
//	static DestoryState ds;
//	return &ds;
//}
//
//void DestoryState::Enter(MyTank *tank)
//{
//	
//}
//
//void DestoryState::Execute(MyTank *tank)
//{
//	tank->setBombFrame(tank->getBombFrame() + 1);
//	tank->setBombImgIndex(tank->getBombFrame() / 10);
//	if (tank->getBombImgIndex() == tank->getBombImgVec().size())
//	{
//		tank->setAlive(false);
//	}
//}
//
//void DestoryState::Exit(MyTank *tank)
//{
//
//}
//
//BulletReadyState* BulletReadyState::getInstance()
//{
//	static BulletReadyState brs;
//	return &brs;
//}
//
//void BulletReadyState::Enter(MyTank* tank)
//{
//	tank->setIsReadyShot(true);
//}
//
//void BulletReadyState::Execute(MyTank* tank)
//{
//	if (!tank->getIsReadyShot())
//	{
//		tank->getShotFSM()->ChangeState(myTankBulletDelayState);
//	}
//}
//
//void BulletReadyState::Exit(MyTank *tank)
//{
//
//}
//
//BulletDelayState* BulletDelayState::getInstance()
//{
//	static BulletDelayState bds;
//	return &bds;
//}
//
//void BulletDelayState::Enter(MyTank *tank)
//{
//	vector<Bullet *> &bulletVec = tank->getBulletVec();
//	int i;
//
//	for (i = 0; i < bulletVec.size(); ++i)
//	{
//		if (!bulletVec[i])
//			break;
//	}
//
//	if (i == bulletVec.size())
//	{
//		tank->getShotFSM()->ChangeState(myTankBulletRunOutState);
//	}
//}
//
//void BulletDelayState::Execute(MyTank *tank)
//{
//	static int shotFrame = 0;
//	
//	shotFrame = (shotFrame + 1) % 200;
//	if (shotFrame == 0)
//	{
//		tank->getShotFSM()->ChangeState(myTankBulletReadyState);
//	}
//}
//
//void BulletDelayState::Exit(MyTank *tank)
//{
//
//}
//
//BulletRunOutState* BulletRunOutState::getInstance()
//{
//	static BulletRunOutState bros;
//	return &bros;
//}
//
//void BulletRunOutState::Enter(MyTank *tank)
//{
//
//}
//
//void BulletRunOutState::Execute(MyTank *tank)
//{
//	vector<Bullet *> &bulletVec = tank->getBulletVec();
//	int i;
//
//	for (i = 0; i < bulletVec.size(); ++i)
//	{
//		if (!bulletVec[i])
//			break;
//	}
//	if (i != bulletVec.size())
//	{
//		tank->getShotFSM()->ChangeState(myTankBulletReadyState);
//	}
//}
//
//void BulletRunOutState::Exit(MyTank *tank)
//{
//
//}
