#include "enemy_tank.h"
#include "enemy_bullet.h"
#include "game.h"
#include "mytank.h"
#include "TankState.h"

#define MAX_BULLET_NUM 4

EnemyTank::EnemyTank(Vector2D pos, Dir dir) : Tank(pos, dir)
{
	aiFrame = 0;
	m_eType = ENEMY_TANK;
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		bulletVec.push_back(NULL);
	}
	m_dSpeed = 0.2;
}

void EnemyTank::AI()
{
	aiFrame = (aiFrame+1)%2000;
	if (aiFrame == 0)
	{
		int temp = static_cast<int>(direction);
		temp = (temp+1)%MoveObject::DIR_NUM;
		direction = static_cast<MoveObject::Dir>(temp);
		angle = (270+45*direction)%360;
		shot();
	}	
}

EnemyTank::~EnemyTank()
{

}
