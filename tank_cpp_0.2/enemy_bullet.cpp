#include "enemy_bullet.h"
#include "game.h"
#include "mytank.h"
#include "Vector2D.h"
#include "utils.h"

EnemyBullet::EnemyBullet(Vector2D pos, Dir direction) : Bullet(pos, direction)
{

}

void EnemyBullet::checkCollision()
{
	const MyTank *myTank = game->getMyTank();
	if (!myTank)
		return;
	Vector2D p = myTank->getDownLeftPoint();
	int width = myTank->getWidth();
	int height = myTank->getHeight();
	
	SDL_Rect rect = {p.x, p.y, width, height};
	Vector2D p2(pos);
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
