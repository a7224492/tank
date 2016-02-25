#include "tank.h"
#include "utils.h"
#include "bullet.h"
#include "C2DMatrix.h"
#include "TankState.h"
#include "my_bullet.h"
#include "enemy_bullet.h"
#include "Vector2D.h"

#define FIRST_SPEED 0.2

Tank::Tank(Vector2D pos, Dir dir) : MoveObject(pos,dir)
	, isReadyShot(true)
	, fsm(new StateMachine<Tank>(this))
	, shotFsm(new StateMachine<Tank>(this))
	, m_pBombEffect(new BombEffect())
    , m_iMaxBulletNum(4)
{
	fsm->SetCurrentState(TankState::standState);
	fsm->SetGlobalState(TankState::globalState);

	shotFsm->SetCurrentState(TankState::bulletReadyState);
}

void Tank::worldTransform(Vector2D &point) const
{
	C2DMatrix mat;
	mat.Rotate(angleToArc(angle));
	mat.Translate(pos.x, pos.y);
	vector<Vector2D> p;
	p.push_back(point);
	mat.TransformVector2Ds(p);
	point = p[0];
}

bool Tank::faceWall() const
{
	Vector2D pLeft = getUpLeftPoint(),pRight = getUpRightPoint();
	worldTransform(pLeft);
	worldTransform(pRight);
	if (!isPointInRect(&screen->clip_rect, pLeft.x, pLeft.y) || !isPointInRect(&screen->clip_rect, pRight.x, pRight.y))
	{
		return true;
	}

	return false;
}

bool Tank::faceOtherTank(const Tank *tank) const
{
	if (!tank)
		return false;
	Vector2D p1 = getUpLeftPoint(),p2 = getUpRightPoint();
	worldTransform(p1);
	worldTransform(p2);

	//contruct rect in tank's native coordinate
	Vector2D p = tank->getDownLeftPoint();
	int width = tank->getWidth();
	int height = tank->getHeight();
	SDL_Rect rect = {p.x, p.y, width, height};

	tank->nativeTransform(p1);
	tank->nativeTransform(p2);
	if (isPointInRect(&rect, p1.x, p1.y) || isPointInRect(&rect, p2.x,p2.y))
		return true;

	return false;
}

void Tank::setWidthHeight(int width, int height)
{
	this->width = width;
	this->height = height;
	Vector2D p[4];
	p[0].x = height/2;
	p[0].y = -width/2;
	p[1].x = height/2;
	p[1].y = width/2;
	p[2].x = -height/2;
	p[2].y = width/2;
	p[3].x = -height/2;
	p[3].y = -width/2;
		
	for (int i = 0; i < 4; ++i)
	{
		pointVec.push_back(p[i]);
	}
}

void Tank::nativeTransform(Vector2D &p) const
{
	C2DMatrix mat;
	mat.Translate(-pos.x,-pos.y);
	mat.Rotate(angleToArc(360-angle));
	vector<Vector2D> pVec;
	pVec.push_back(p);
	mat.TransformVector2Ds(pVec);
	p = pVec[0];
}



void Tank::updateBullet()
{
	for (size_t i = 0; i < bulletVec.size(); ++i)
	{
		if (bulletVec[i])
		{
			bulletVec[i]->update();
			if (!bulletVec[i]->getAlive())
			{
				delete bulletVec[i];
				bulletVec[i] = NULL;
			}
		}
	}
}

void Tank::drawBullet()
{
	for (size_t i = 0; i < bulletVec.size(); ++i)
	{
		if (bulletVec[i])
			bulletVec[i]->draw();
	}
}

Tank::~Tank()
{

}

void Tank::update()
{
	checkKeyState();
	
	if (m_bAlive)
	{
		shotFsm->Update();
		updateBullet();
	}
	fsm->Update();
}

void Tank::draw()
{
	if (!(fsm->CurrentState() == TankState::destoryState))
	{
		SDL_Rect rect = { pos.x - imgs[direction]->w / 2, pos.y - imgs[direction]->h / 2, 0, 0 };
		SDL_BlitSurface(imgs[direction], NULL, screen, &rect);
	} else{
		m_pBombEffect->draw(screen);
	}
	drawBullet();
}

void Tank::checkKeyState()
{
	Uint8 *keystate = SDL_GetKeyState(0);

	if (m_eType == MY_TANK)
	{
		if (keystate[SDLK_w])
		{
			velocity.y = -1;
		} else if (keystate[SDLK_s])
		{
			velocity.y = 1;
		} else{
			velocity.y = 0;
		}

		if (keystate[SDLK_a])
		{
			velocity.x = -1;
		} else if (keystate[SDLK_d])
		{
			velocity.x = 1;
		} else{
			velocity.x = 0;
		}
		if (keystate[SDLK_j]){
			shot();
		}
	}
	if (m_eType == ENEMY_TANK){
		if (keystate[SDLK_UP])
		{
			velocity.y = -1;
		} else if (keystate[SDLK_DOWN])
		{
			velocity.y = 1;
		} else{
			velocity.y = 0;
		}

		if (keystate[SDLK_LEFT])
		{
			velocity.x = -1;
		} else if (keystate[SDLK_RIGHT])
		{
			velocity.x = 1;
		} else{
			velocity.x = 0;
		}
		if (keystate[SDLK_k]){
			shot();
		}
	}

	if (velocity.x == 1){
		if (velocity.y == 1){
			direction = MoveObject::DOWN_RIGHT;
		}else if (velocity.y == -1){
			direction = MoveObject::UP_RIGHT;
		}else{
			direction = MoveObject::RIGHT;
		}
	}else if (velocity.x == -1){
		if (velocity.y == 1){
			direction = MoveObject::DOWN_LEFT;
		}else if (velocity.y == -1){
			direction = MoveObject::UP_LEFT;
		}else {
			direction = MoveObject::LEFT;
		}
	}else {
		if (velocity.y == 1){
			direction = MoveObject::DOWN;
		}else if (velocity.y == -1){
			direction = MoveObject::UP;
		}
	}
	velocity.Normalize();
	velocity *= m_dSpeed;
}

void Tank::shot()
{
	if (!isReadyShot)
		return;
	isReadyShot = false;
	size_t i;
	for (i = 0; i < bulletVec.size(); ++i)
	{
		if (!bulletVec[i])
			break;

		if (!bulletVec[i]->getAlive())
			break;
	}
	if (i == bulletVec.size())
		return;
	Vector2D bulletPos(25, 0);
	worldTransform(bulletPos);
	Bullet *bullet = NULL;
	if (m_eType == MY_TANK)
	{
		bullet = new MyBullet(bulletPos, direction);
	} else if (m_eType == ENEMY_TANK){
		bullet = new EnemyBullet(bulletPos, direction);
	}
	bullet->setScreen(screen);
	bullet->setGame(game);
	bullet->setDirImg(bulletImgs[direction], direction);
	if (bulletVec[i])
		delete bulletVec[i];
	bulletVec[i] = bullet;
}
