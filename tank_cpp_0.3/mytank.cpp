#include "mytank.h"
#include "enemy_tank.h"
#include "my_bullet.h"
#include "C2DMatrix.h"
#include "Vector2D.h"
#include "game.h"
#include "TankState.h"
#include "MyTankState.h"
#include <cmath>
#include <SDL/SDL_rotozoom.h>

#define MOVE_DELAY 4000
#define MAX_BULLET_NUM 4
#define FIRST_SPEED 0.2

MyTank::MyTank(Vector2D pos, Dir direction): Tank(pos, direction)
{
	m_dSpeed = FIRST_SPEED;
	m_eType = MY_TANK;

	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		bulletVec.push_back(NULL);
	}
}

MyTank::~MyTank()
{

}


