#ifndef TANK_H
#define TANK_H

#include "move_object.h"
#include "Vector2D.h"
#include "StateMachine.h"
#include "BombEffect.h"
#include <vector>

using namespace std;

class Bullet;

enum TankType{
	MY_TANK,
	ENEMY_TANK
};

class Tank : public MoveObject
{
public:
	Tank(Vector2D pos, Dir dir);
	virtual ~Tank();

	virtual void update();
	virtual void draw();

	void setWidthHeight(int width, int height);
	void nativeTransform(Vector2D &p) const;
	void worldTransform(Vector2D &point) const;

	bool faceWall() const;
	bool faceOtherTank(const Tank *tank) const;

	inline void setWidth(int width){
		this->width = width;
	}
	inline void setHeight(int height){
		this->height = height;
	}
	inline int getWidth() const{
		return this->width;
	}
	inline int getHeight() const{
		return this->height;
	}
	inline Vector2D getUpLeftPoint() const{
		return pointVec[UP_LEFT];
	}
	inline Vector2D getUpRightPoint() const{
		return pointVec[UP_RIGHT];
	}
	inline Vector2D getDownRightPoint() const{
		return pointVec[DOWN_RIGHT];
	}
	inline Vector2D getDownLeftPoint() const{
		return pointVec[DOWN_LEFT];
	}
	inline void setBulletImg(SDL_Surface *img, Dir dir){
		bulletImgs[dir] = img;
	}
	inline bool getIsReadyShot() const{
		return this->isReadyShot;
	}
	inline void setIsReadyShot(bool isReadyShot){
		this->isReadyShot = isReadyShot;
	}
	inline vector<Bullet *>& getBulletVec(){
		return bulletVec;
	}
	inline StateMachine<Tank>* getFSM() const{
		return this->fsm;
	}
	inline StateMachine<Tank>* getShotFSM() const {
		return this->shotFsm;
	}
	inline void addBombImg(SDL_Surface *img){
		m_pBombEffect->addBombImg(img);
	}
	inline BombEffect* getBombEffect() const{
		return m_pBombEffect;
	}
	inline void setBombEffect(BombEffect *bombEffect){
		m_pBombEffect = bombEffect;
	}
	inline TankType getType() const {
		return m_eType;
	}
private:
	enum {
		UP_LEFT = 0,
		UP_RIGHT,
		DOWN_RIGHT,
		DOWN_LEFT
	};
protected:
	enum {
		BOMB_FRAME_NUM = 10
	};

	TankType m_eType;

	StateMachine<Tank> *fsm;
	StateMachine<Tank> *shotFsm;

	vector<Bullet *> bulletVec;
	vector<Vector2D> pointVec;
	
	SDL_Surface *bulletImgs[DIR_NUM];

	int width,height;

	bool isReadyShot;

	BombEffect *m_pBombEffect;
	
	
	void updateBullet();
	void drawBullet();
	void checkKeyState();
	void shot();
};

#endif