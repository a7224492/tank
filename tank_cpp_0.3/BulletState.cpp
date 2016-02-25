#include "BulletState.h"
#include "bullet.h"
#include "BombEffect.h"
#include "ResourceManager.h"
#include "game.h"
#include <vector>

using namespace BulletStateName;

MoveState* MoveState::getInstance()
{
	static MoveState ms;
	return &ms;
}

void MoveState::Enter(Bullet *bullet)
{
	bullet->setVelocity(directionVelocity[bullet->getDirection()]);
	bullet->getVelocity().Normalize();
	bullet->setVelocity(bullet->getVelocity()*bullet->getSpeed());
}

void MoveState::Execute(Bullet* bullet)
{
	bullet->setPos(bullet->getPos()+bullet->getVelocity()*bullet->getGame()->getElapsedTime());
	bullet->checkCollision();
	if (!isPointInRect(&bullet->getGame()->getScreen()->clip_rect, bullet->getPos().x, bullet->getPos().y))
	{
		bullet->getFSM()->ChangeState(BulletStateName::destoryState);
	}
}

void MoveState::Exit(Bullet* bullet)
{

}

DestoryState* DestoryState::getInstance()
{
	static DestoryState ds;
	return &ds;
}

void DestoryState::Enter(Bullet *bullet)
{
	const std::vector<SDL_Surface* >& bombImg = resourceMgr->getBulletBombEffectImg();

	bullet->setBombEffect(new BombEffect());
	bullet->getBombEffect()->setPos(bullet->getPos());
	for (int i = 0; i < bombImg.size(); ++i){
		bullet->getBombEffect()->addBombImg(bombImg[i]);
	}
	
}

void DestoryState::Execute(Bullet *bullet)
{
	bullet->getBombEffect()->update();
	if (bullet->getBombEffect()->getFinish())
		bullet->setAlive(false);
}

void DestoryState::Exit(Bullet *bullet)
{

}