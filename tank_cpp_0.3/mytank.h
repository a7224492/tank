#ifndef MYTANK_H
#define MYTANK_H

#include <SDL/SDL.h>
#include <vector>
#include "tank.h"
#include "MoveObjectDirection.h"
#include "StateMachine.h"

using namespace std;

class Bullet;

class MyTank : public Tank
{
public:
	MyTank(Vector2D pos, Dir direction);
	virtual ~MyTank();
	
private:
	
};

#endif