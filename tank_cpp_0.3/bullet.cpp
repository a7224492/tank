#include "bullet.h"
#include "utils.h"
#include "game.h"
#include "enemy_tank.h"
#include "BulletState.h"

Bullet::Bullet(Vector2D pos, Dir direction) : MoveObject(pos, direction)
{
	m_dSpeed = 0.4;
	fsm = new StateMachine<Bullet>(this);
	velocity = directionVelocity[direction];
	velocity.Normalize();
	velocity *= m_dSpeed;
	fsm->SetCurrentState(BulletStateName::moveState);
}

void Bullet::update()
{
	SDL_Rect rect = {pos.x-imgs[direction]->w, pos.y-imgs[direction]->h, imgs[direction]->w, imgs[direction]->h};
	//SDL_Rect screenRect = {0,0,screen->w, screen->h};
	

	fsm->Update();
}

void Bullet::draw()
{
	if (fsm->CurrentState() != BulletStateName::destoryState){
		SDL_Rect rect = {pos.x-imgs[direction]->w/2, pos.y-imgs[direction]->h/2, 0, 0};	
		SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
	}else{
		m_pBombEffect->draw(game->getScreen());
	}
}

Bullet::~Bullet()
{

}
