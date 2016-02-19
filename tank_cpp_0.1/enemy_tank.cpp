#include "enemy_tank.h"
#include "enemy_bullet.h"
#include "game.h"
#include "mytank.h"

#define MAX_BULLET_NUM 4

EnemyTank::EnemyTank(int x, int y, Dir dir) : Tank(x, y, dir)
{
	state = MOVE;
	aiFrame = 0;
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		bulletVec.push_back(NULL);
	}
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
		SDL_Rect rect = {x-imgs[direction]->w/2, y-imgs[direction]->h/2, 0, 0};
		SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
		drawBullet();
	}else{
		SDL_Rect rect = {x-bombImgVec[bombImgIndex]->w/2, y-bombImgVec[bombImgIndex]->h/2, 0, 0};
		SDL_BlitSurface(bombImgVec[bombImgIndex], NULL, screen, &rect);
	}
}

void EnemyTank::executeState()
{
	const MyTank *myTank;
	switch (state)
	{
	case MOVE:
		moveFrame = (moveFrame+1)%15;
		if (moveFrame != 0)
		{
			return;
		}
		if (angle % 90 == 0)
		{
			speed.x = MoveObject::speedVectorX[direction]*3;
			speed.y = MoveObject::speedVectorY[direction]*3;
		}else{
			speed.x = MoveObject::speedVectorX[direction]*2;
			speed.y = MoveObject::speedVectorY[direction]*2;
		}

		x += speed.x;
		y += speed.y;
		if (faceWall())
		{
			x -= speed.x;
			y -= speed.y;
		}
		myTank = game->getMyTank();
		if (faceOtherTank(myTank))
		{
			x -= speed.x;
			y -= speed.y;
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
	SPoint bulletPos(25,0);
	worldTransform(bulletPos);
	EnemyBullet *bullet = new EnemyBullet(bulletPos.x, bulletPos.y, direction);
	bullet->setScreen(screen);
	bullet->setGame(game);
	bullet->setDirImg(bulletImgs[direction], direction);
	bulletVec[i] = bullet;
}

EnemyTank::~EnemyTank()
{

}
