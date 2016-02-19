#include "my_bullet.h"
#include "game.h"
#include "SVector2D.h"
#include "enemy_tank.h"
#include "utils.h"

MyBullet::MyBullet(int x, int y, Dir direction) : Bullet(x, y, direction)
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
		if (!enemy)
			continue;
		SPoint p = enemy->getDownLeftPoint();
		int width = enemy->getWidth();
		int height = enemy->getHeight();
		SDL_Rect rect = {p.x, p.y, width, height};
		SPoint p2;
		p2.x = x;
		p2.y = y;
		enemy->nativeTransform(p2);
		if (isPointInRect(&rect, p2.x, p2.y))
		{
			game->myBulletShotEnemy(i);
			changeStateToDestory();
			break;
		}
	}
}

MyBullet::~MyBullet()
{

}
