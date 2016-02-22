#ifndef BULLETSTATE_H
#define BULLETSTATE_H

#include "State.h"

class Bullet;

namespace BulletStateName{

class MoveState : public State<Bullet>
{
private:
	MoveState(){}
	MoveState(const MoveState &ms);
	MoveState& operator= (const MoveState &ms);
public:
	virtual ~MoveState(){}
	static MoveState* getInstance();

	virtual void Enter(Bullet *);
	virtual void Execute(Bullet*);
	virtual void Exit(Bullet*);
};

class DestoryState : public State<Bullet>
{
private:
	DestoryState(){}
	DestoryState(const DestoryState &ds);
	DestoryState& operator= (const DestoryState &ds);
public:
	virtual ~DestoryState(){}
	static DestoryState* getInstance();

	virtual void Enter(Bullet *bullet) override;
	virtual void Execute(Bullet *bullet) override;
	virtual void Exit(Bullet *bullet) override;
};

#define moveState MoveState::getInstance()
#define destoryState DestoryState::getInstance()
}

#endif
