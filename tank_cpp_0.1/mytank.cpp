#include "mytank.h"
#include "enemy_tank.h"
#include "my_bullet.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "game.h"
#include <SDL/SDL_rotozoom.h>

#define MOVE_DELAY 4000
#define MAX_BULLET_NUM 4

MyTank::MyTank(int x, int y, Dir direction): Tank(x,y, direction)
{
	control.x = 0;
	control.y = 0;
	state = STAND;
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		bulletVec.push_back(NULL);
	}
}

void MyTank::update()
{
	Uint8 *keystate = SDL_GetKeyState(0);
	if (!isDestoryState())
	{
		changeToStandState();
		if(keystate[SDLK_w])
		{
			control.y = -1;
		}else if (keystate[SDLK_s])
		{
			control.y = 1; 
		}else{
			control.y = 0;
		}
		if (keystate[SDLK_a])
		{
			control.x = -1;
		}else if (keystate[SDLK_d])
		{
			control.x = 1;
		}else{
			control.x = 0;
		}
		/************************************************************************/
		/* test                                                                     */
		/************************************************************************/
		if (keystate[SDLK_t])
		{
			SPoint point(1,1);
			nativeTransform(point);
			int x = 10;
		}
		if (control.x != 0 || control.y != 0)
		{
			changeToMoveState();
		}
		if (shotFrame != 0)
			shotFrame = (shotFrame+1)%300;
		if (keystate[SDLK_j]){
			shot();
		}
	}
	
	updateBullet();
	excuteState();
}

void MyTank::excuteState()
{
	switch (state)
	{
	case MOVE: 
		moveFrame = (moveFrame+1)%20;
		if (moveFrame != 0)
		{
			return;
		}	
		if (control.x > 0)
		{
			if (control.y > 0)
			{
				direction = MoveObject::DOWN_RIGHT;
			}else if (control.y < 0){
				direction = MoveObject::UP_RIGHT;
			}else{
				direction = MoveObject::RIGHT;
			}
		}else if (control.x < 0){
			if (control.y > 0)
			{
				direction = MoveObject::DOWN_LEFT;
			}else if (control.y < 0){
				direction = MoveObject::UP_LEFT;
			}else{
				direction = MoveObject::LEFT;
			}
		}else{
			if (control.y > 0)
			{
				direction = MoveObject::DOWN;
			}else{
				direction = MoveObject::UP;
			}
		}
		if (angle%90 == 0)
		{
			speed.x = control.x*3;
			speed.y = control.y*3;
		}else
		{
			speed.x = control.x*2;
			speed.y = control.y*2;
		}
		
		angle = (270+45*direction)%360;

		
		x += speed.x;
		y += speed.y;

		if (faceWall())
		{
			x -= speed.x;
			y -= speed.y;
		}
		for (int i = 0; i < game->getEnemyTankNum(); ++i)
		{
			const EnemyTank *enemy = game->getEnemyTank(i);
			if (enemy && faceOtherTank(enemy))
			{
				x -= speed.x;
				y -= speed.y;
			}
		}
		
		break;
	case STAND:
		break;
	
	case DESTORY:
		bombFrame += 1;
		if ((bombFrame/10) == bombImgVec.size())
			game->myTankDestory();
			
		break;
	}
}

void MyTank::draw(SDL_Surface *background)
{
	if (state != DESTORY)
	{
		SDL_Rect rect = {x-imgs[direction]->w/2,y-imgs[direction]->h/2, 0, 0};
		SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
		drawBullet();
	}else{
		SDL_Rect rect = {x-bombImgVec[bombFrame/10]->w/2, y-bombImgVec[bombFrame/10]->h/2, 0, 0};
		SDL_BlitSurface(bombImgVec[bombFrame/10], NULL, screen, &rect);
	}
}

void MyTank::worldTransformRect(SDL_Rect &rect)
{
	SPoint temp(rect.x,rect.y);
	worldTransform(temp);
	rect.x = temp.x;
	rect.y = temp.y;
}

void MyTank::shot()
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
	Bullet *bullet = new MyBullet(bulletPos.x, bulletPos.y, direction);
	bullet->setScreen(screen);
	bullet->setGame(game);
	bullet->setDirImg(bulletImgs[direction], direction);
	bulletVec[i] = bullet;
}

MyTank::~MyTank()
{

}
