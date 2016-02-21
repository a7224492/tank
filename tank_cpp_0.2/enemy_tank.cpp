#include "enemy_tank.h"
#include "enemy_bullet.h"
#include "game.h"
#include "mytank.h"

#define MAX_BULLET_NUM 4

EnemyTank::EnemyTank(Vector2D pos, Dir dir) : Tank(pos, dir)
{
	state = MOVE;
	aiFrame = 0;
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		bulletVec.push_back(NULL);
	}
	m_dSpeed = 0.2;
}

void EnemyTank::update()
{
	if (!isDestoryState())
	{
		AI();
		if (shotFrame != 0)
		{
			shotFrame = (shotFrame+1)%300;
		}
	}
	updateBullet();
	executeState();
}

void EnemyTank::draw()
{
	if (!isDestoryState())
	{
		SDL_Rect rect = {pos.x-imgs[direction]->w/2, pos.y-imgs[direction]->h/2, 0, 0};
		SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
		drawBullet();
	}else{
		SDL_Rect rect = {pos.x-bombImgVec[bombImgIndex]->w/2, pos.y-bombImgVec[bombImgIndex]->h/2, 0, 0};
		SDL_BlitSurface(bombImgVec[bombImgIndex], NULL, screen, &rect);
	}
}

void EnemyTank::executeState()
{
	const MyTank *myTank;
	switch (state)
	{
	case MOVE:
		if (angle % 90 == 0)
		{
			speed.x = MoveObject::speedVectorX[direction]*m_dSpeed;
			speed.y = MoveObject::speedVectorY[direction]*m_dSpeed;
		}else{
			speed.x = MoveObject::speedVectorX[direction]*sqrt(m_dSpeed*m_dSpeed/2);
			speed.y = MoveObject::speedVectorY[direction]*sqrt(m_dSpeed*m_dSpeed/2);
		}

		pos += speed;

		if (faceWall())
		{
			pos -= speed;
		}
		myTank = game->getMyTank();
		if (faceOtherTank(myTank))
		{
			pos -= speed;
		}
		
		break;
	case STAND:
		break;
	case DESTORY:
		bombFrame += 1;
		bombImgIndex = bombFrame/BOMB_FRAME_NUM;
 		if (bombImgIndex == bombImgVec.size())
		{
			game->enemyTankDestory(this);
		}
		break;
	}
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

void EnemyTank::shot()
{
	if (shotFrame != 0)
	{
		return;
	}
	shotFrame++;
	size_t i;
	for (i = 0; i < bulletVec.size(); ++i)
	{
		if (bulletVec[i] == NULL)
			break;
	}
	if (i == bulletVec.size())
		return;
	Vector2D bulletPos(25,0);
	worldTransform(bulletPos);
	EnemyBullet *bullet = new EnemyBullet(bulletPos, direction);
	bullet->setScreen(screen);
	bullet->setGame(game);
	bullet->setDirImg(bulletImgs[direction], direction);
	bulletVec[i] = bullet;
}

void EnemyTank::changeDirection(Dir direction)
{
	
}

EnemyTank::~EnemyTank()
{

}
