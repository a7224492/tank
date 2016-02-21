#include "bullet.h"
#include "utils.h"
#include "game.h"
#include "enemy_tank.h"

Bullet::Bullet(Vector2D pos, Dir direction) : MoveObject(pos, direction), isAlive(true)
{
	m_dSpeed = 0.4;
	changeStateToMove();
}

void Bullet::update()
{
	SDL_Rect rect = {pos.x-imgs[direction]->w, pos.y-imgs[direction]->h, imgs[direction]->w, imgs[direction]->h};
	//SDL_Rect screenRect = {0,0,screen->w, screen->h};
	if (!isPointInRect(&screen->clip_rect, pos.x, pos.y))
	{
		changeStateToDestory();
	}
	excuteState();
}

void Bullet::excuteState()
{
	switch (state)
	{
	case MOVE:
		pos += velocity;

		checkCollision();
		
		break;
	case DESTORY:
		break;
	}
}

void Bullet::draw()
{
	SDL_Rect rect = {pos.x-imgs[direction]->w/2, pos.y-imgs[direction]->h/2, 0, 0};	
	SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
}

void Bullet::changeStateToMove()
{
	state = MOVE;
	if (((int)angle)%90 == 0)
	{
		velocity.x = MoveObject::speedVectorX[direction]*m_dSpeed;
		velocity.y = MoveObject::speedVectorY[direction]*m_dSpeed;
	}else{
		velocity.x = MoveObject::speedVectorX[direction]*sqrt(m_dSpeed*m_dSpeed/2);
		velocity.y = MoveObject::speedVectorY[direction]*sqrt(m_dSpeed*m_dSpeed/2);
	}
}

Bullet::~Bullet()
{

}
