#ifndef TANKSTATE_H
#define TANKSTATE_H

#include "State.h"

class Tank;

namespace TankState{

class GlobalState : public State<Tank>
{
public:
	~GlobalState(){}
	static GlobalState* getInstance();

	virtual void Enter(Tank *tank) {};
	virtual void Execute(Tank* tank);
	virtual void Exit(Tank *tank) {};
private:
	GlobalState(){};
	GlobalState(const GlobalState &);
	GlobalState& operator= (const GlobalState &);
};

#define globalState GlobalState::getInstance()

class MoveState : public State<Tank>
{
private:
	MoveState(){}
	MoveState(const MoveState &ms);
	MoveState& operator= (const MoveState &ms);
public:
	virtual ~MoveState(){}
	static MoveState* getInstance();

	virtual void Enter(Tank *);
	virtual void Execute(Tank*);
	virtual void Exit(Tank*);
};

class StandState : public State<Tank>
{
private:
	StandState(){};
	StandState(const StandState &ss);
	StandState& operator=(const StandState &ss);

public:
	virtual ~StandState(){}
	static StandState* getInstance();

	virtual void Enter(Tank *tank) override;
	virtual void Execute(Tank *tank) override;
	virtual void Exit(Tank *tank) override;

};

class DestoryState : public State<Tank>
{
private:
	DestoryState(){}
	DestoryState(const DestoryState &ds);
	DestoryState& operator= (const DestoryState &ds);
public:
	virtual ~DestoryState(){}
	static DestoryState* getInstance();

	virtual void Enter(Tank *tank) override;
	virtual void Execute(Tank *tank) override;
	virtual void Exit(Tank *tank) override;
};

#define moveState MoveState::getInstance()
#define standState StandState::getInstance()
#define destoryState DestoryState::getInstance()

class BulletReadyState : public State<Tank>
{
private:
	BulletReadyState(){}
	BulletReadyState(const BulletReadyState &);
	BulletReadyState& operator= (const BulletReadyState &);
public:
	~BulletReadyState(){}
	static BulletReadyState* getInstance();

	virtual void Enter(Tank* tank) override;
	virtual void Execute(Tank* tank) override;
	virtual void Exit(Tank *tank) override;
};

class BulletDelayState : public State<Tank>
{
private:
	BulletDelayState(){}
	BulletDelayState(const BulletDelayState &);
	BulletDelayState& operator= (const BulletDelayState &);
public:
	~BulletDelayState(){};
	static BulletDelayState* getInstance();

	virtual void Enter(Tank *tank) override;
	virtual void Execute(Tank *Tank) override;
	virtual void Exit(Tank *tank) override;
};

class BulletRunOutState : public State<Tank>
{
private:
	BulletRunOutState(){}
	BulletRunOutState(const BulletRunOutState &);
	BulletRunOutState& operator= (const BulletRunOutState &);
public:
	~BulletRunOutState(){};
	static BulletRunOutState* getInstance();

	virtual void Enter(Tank *tank) override;
	virtual void Execute(Tank *tank) override;
	virtual void Exit(Tank *tank) override;
};

#define bulletReadyState BulletReadyState::getInstance()
#define bulletDelayState BulletDelayState::getInstance()
#define bulletRunOutState BulletRunOutState::getInstance()

}

#endif