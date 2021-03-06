#ifndef TANK_H
#define TANK_H

#include "move_object.h"
#include "SVector2D.h"
#include <vector>

using namespace std;

class Bullet;

class Tank : public MoveObject
{
public:
	Tank(Vector2D pos, Dir dir);
	virtual ~Tank();
	void setWidthHeight(int width, int height);
	void nativeTransform(Vector2D &p) const;
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
	inline void addBombImg(SDL_Surface *img){
		bombImgVec.push_back(img);
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
	int width,height;
	vector<Bullet *> bulletVec;
	int shotFrame;
	int bombFrame;
	int bombImgIndex;
	SDL_Surface *bulletImgs[DIR_NUM];
	vector<Vector2D> pointVec;
	vector<SDL_Surface *> bombImgVec;
	void worldTransform(Vector2D &point);
	bool faceWall();
	bool faceOtherTank(const Tank *tank);
	void updateBullet();
	void drawBullet();
};

#endif