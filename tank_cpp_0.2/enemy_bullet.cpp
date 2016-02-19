#include "enemy_bullet.h"
#include "game.h"
#include "mytank.h"
#include "SVector2D.h"
#include "utils.h"

EnemyBullet::EnemyBullet(int x, int y, Dir direction) : Bullet(x, y, direction)
{

}

void EnemyBullet::checkCollision()
{
	const MyTank *myTank = game->getMyTank();
	if (!myTank)
		return;
	SPoint p = myTank->getDownLeftPoint();
	int width = myTank->getWidth();
	int height = myTank->getHeight();
	
	SDL_Rect rect = {p.x, p.y, width, height};
	SPoint p2(x,y);
	myTank->nativeTransform(p2);
	if (isPointInRect(&rect, p2.x, p2.y))
	{
		if (!myTank->isDestoryState())
		{
			game->myTankChangeToDestory();
			changeStateToDestory();
		}
	}
}

EnemyBullet::~EnemyBullet()
{

}
