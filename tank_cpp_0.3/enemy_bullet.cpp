#include "enemy_bullet.h"
#include "game.h"
#include "mytank.h"
#include "Vector2D.h"
#include "utils.h"
#include "MyTankState.h"
#include "TankState.h"
#include "BulletState.h"

EnemyBullet::EnemyBullet(Vector2D pos, Dir direction) : Bullet(pos, direction)
{
	m_eType = ENEMY_BULLET;
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
		if (!(myTank->getFSM()->CurrentState() == TankState::destoryState))
		{
			//game->myTankChangeToDestory();
			game->getMyTank()->getFSM()->ChangeState(TankState::destoryState);
			getFSM()->ChangeState(BulletStateName::destoryState);
		}
	}
}

EnemyBullet::~EnemyBullet()
{

}
