#include "bullet.h"
#include "utils.h"
#include "game.h"
#include "enemy_tank.h"

Bullet::Bullet(int x, int y, Dir direction) : MoveObject(x,y,direction)
{
	changeStateToMove();
	isAlive = true;
}

void Bullet::update()
{
	SDL_Rect rect = {x-imgs[direction]->w, y-imgs[direction]->h, imgs[direction]->w, imgs[direction]->h};
	//SDL_Rect screenRect = {0,0,screen->w, screen->h};
	if (!isPointInRect(&screen->clip_rect, x, y))
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
		moveFrame = (moveFrame+1)%10;
		if (moveFrame != 0)
			return;
		x += speed.x;
		y += speed.y;

		checkCollision();
		
		break;
	case DESTORY:
		break;
	}
}

void Bullet::draw()
{
	//SDL_BlitSurface(background, &oldRegion, screen, &oldRegion);
	SDL_Rect rect = {x-imgs[direction]->w/2, y-imgs[direction]->h/2, 0, 0};	
	SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
	//oldRegion = rect;
}

void Bullet::changeStateToMove()
{
	state = MOVE;
	if (angle%90 == 0)
	{
		speed.x = MoveObject::speedVectorX[direction]*3;
		speed.y = MoveObject::speedVectorY[direction]*3;
	}else{
		speed.x = MoveObject::speedVectorX[direction]*2;
		speed.y = MoveObject::speedVectorY[direction]*2;
	}
}

Bullet::~Bullet()
{

}
