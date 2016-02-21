#ifndef MYTANKFSM_H
#define MYTANKFSM_H

#include "State.h"

//class MyTank;
//
//class MoveState : public State<MyTank>
//{
//private:
//	MoveState(){}
//	MoveState(const MoveState &ms);
//	MoveState& operator= (const MoveState &ms);
//public:
//	virtual ~MoveState(){}
//	static MoveState* getInstance();
//
//	virtual void Enter(MyTank *);
//	virtual void Execute(MyTank*);
//	virtual void Exit(MyTank*);
//};
//
//class StandState : public State<MyTank>
//{
//private:
//	StandState(){};
//	StandState(const StandState &ss);
//	StandState& operator=(const StandState &ss);
//
//public:
//	virtual ~StandState(){}
//	static StandState* getInstance();
//
//	virtual void Enter(MyTank *tank) override;
//	virtual void Execute(MyTank *tank) override;
//	virtual void Exit(MyTank *tank) override;
//
//};
//
//class DestoryState : public State<MyTank>
//{
//private:
//	DestoryState(){}
//	DestoryState(const DestoryState &ds);
//	DestoryState& operator= (const DestoryState &ds);
//public:
//	virtual ~DestoryState(){}
//	static DestoryState* getInstance();
//
//	virtual void Enter(MyTank *tank) override;
//	virtual void Execute(MyTank *tank) override;
//	virtual void Exit(MyTank *tank) override;
//};
//
//#define myTankMoveState MoveState::getInstance()
//#define myTankStandState StandState::getInstance()
//#define myTankDestoryState DestoryState::getInstance()
//
//class BulletReadyState : public State<MyTank>
//{
//private:
//	BulletReadyState(){}
//	BulletReadyState(const BulletReadyState &);
//	BulletReadyState& operator= (const BulletReadyState &);
//public:
//	~BulletReadyState(){}
//	static BulletReadyState* getInstance();
//
//	virtual void Enter(MyTank* tank) override;
//	virtual void Execute(MyTank* tank) override;
//	virtual void Exit(MyTank *tank) override;
//};
//
//class BulletDelayState : public State<MyTank>
//{
//private:
//	BulletDelayState(){}
//	BulletDelayState(const BulletDelayState &);
//	BulletDelayState& operator= (const BulletDelayState &);
//public:
//	~BulletDelayState(){};
//	static BulletDelayState* getInstance();
//
//	virtual void Enter(MyTank *tank) override;
//	virtual void Execute(MyTank *Tank) override;
//	virtual void Exit(MyTank *tank) override;
//};
//
//class BulletRunOutState : public State<MyTank>
//{
//private:
//	BulletRunOutState(){}
//	BulletRunOutState(const BulletRunOutState &);
//	BulletRunOutState& operator= (const BulletRunOutState &);
//public:
//	~BulletRunOutState(){};
//	static BulletRunOutState* getInstance();
//
//	virtual void Enter(MyTank *tank) override;
//	virtual void Execute(MyTank *tank) override;
//	virtual void Exit(MyTank *tank) override;
//};
//
//#define myTankBulletReadyState BulletReadyState::getInstance()
//#define myTankBulletDelayState BulletDelayState::getInstance()
//#define myTankBulletRunOutState BulletRunOutState::getInstance()

#endif