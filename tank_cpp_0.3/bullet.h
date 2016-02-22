#ifndef BULLET_H
#define BULLET_H

#include "move_object.h"
#include "StateMachine.h"

class BombEffect;

class Bullet : public MoveObject
{
public:
	enum Type{
		MY_BULLET,
		ENEMY_BULLET
	};

	Bullet(Vector2D pos, Dir direction);
	virtual ~Bullet();
	
	void update();
	void draw();

	inline StateMachine<Bullet>* getFSM() const {
		return fsm;
	}
	inline BombEffect* getBombEffect() const {
		return m_pBombEffect;
	}
	inline void setBombEffect(BombEffect *bombEffect){
		m_pBombEffect = bombEffect;
	}
	virtual void checkCollision(){};
protected:
	StateMachine<Bullet> *fsm;
	BombEffect *m_pBombEffect;
	Type m_eType;
};

#endif