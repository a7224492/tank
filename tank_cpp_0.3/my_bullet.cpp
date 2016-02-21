#include "my_bullet.h"
#include "game.h"
#include "Vector2D.h"
#include "enemy_tank.h"
#include "utils.h"
#include "TankState.h"

MyBullet::MyBullet(Vector2D pos, Dir direction) : Bullet(pos, direction)
{

}

void MyBullet::checkCollision()
{
	/************************************************************************/
	/* bullet destory enemy tank                                                                     */
	/************************************************************************/
	for (int i = 0; i < game->getEnemyTankNum(); ++i)
	{
		const EnemyTank *enemy = game->getEnemyTank(i);
		if (!enemy->getAlive())
			continue;
		Vector2D p = enemy->getDownLeftPoint();
		int width = enemy->getWidth();
		int height = enemy->getHeight();
		SDL_Rect rect = {p.x, p.y, width, height};
		Vector2D p2(pos);
		enemy->nativeTransform(p2);
		if (isPointInRect(&rect, p2.x, p2.y))
		{
			enemy->getFSM()->ChangeState(TankState::destoryState);
			changeStateToDestory();
			break;
		}
	}
}

MyBullet::~MyBullet()
{

}
