#include "mytank.h"
#include "enemy_tank.h"
#include "my_bullet.h"
#include "C2DMatrix.h"
#include "Vector2D.h"
#include "game.h"
#include <cmath>
#include <SDL/SDL_rotozoom.h>

#define MOVE_DELAY 4000
#define MAX_BULLET_NUM 4

MyTank::MyTank(Vector2D pos, Dir direction): Tank(pos, direction)
{
	control.x = 0;
	control.y = 0;
	state = STAND;
	for (int i = 0; i < MAX_BULLET_NUM; ++i)
	{
		bulletVec.push_back(NULL);
	}
	m_dSpeed = 0.2;
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
			Vector2D point(1,1);
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
			speed.x = control.x*m_dSpeed;
			speed.y = control.y*m_dSpeed;
		}else
		{
			speed.x = control.x*sqrt(m_dSpeed*m_dSpeed/2);
			speed.y = control.y*sqrt(m_dSpeed*m_dSpeed/2);
		}
		
		angle = (270+45*direction)%360;
		
		pos += speed;

		if (faceWall())
		{
			pos -= speed;
		}
		for (int i = 0; i < game->getEnemyTankNum(); ++i)
		{
			const EnemyTank *enemy = game->getEnemyTank(i);
			if (enemy && faceOtherTank(enemy))
			{
				pos -= speed;
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
		SDL_Rect rect = {pos.x-imgs[direction]->w/2,pos.y-imgs[direction]->h/2, 0, 0};
		SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
		drawBullet();
	}else{
		SDL_Rect rect = {pos.x-bombImgVec[bombFrame/10]->w/2, pos.y-bombImgVec[bombFrame/10]->h/2, 0, 0};
		SDL_BlitSurface(bombImgVec[bombFrame/10], NULL, screen, &rect);
	}
}

void MyTank::worldTransformRect(SDL_Rect &rect)
{
	Vector2D temp(rect.x,rect.y);
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
	Vector2D bulletPos(25,0);
	worldTransform(bulletPos);
	Bullet *bullet = new MyBullet(bulletPos, direction);
	bullet->setScreen(screen);
	bullet->setGame(game);
	bullet->setDirImg(bulletImgs[direction], direction);
	bulletVec[i] = bullet;
}

MyTank::~MyTank()
{

}
