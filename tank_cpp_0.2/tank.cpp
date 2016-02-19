#include "tank.h"
#include "utils.h"
#include "bullet.h"
#include "C2DMatrix.h"

Tank::Tank(int x,int y, Dir dir) : MoveObject(x,y,dir)
{
	shotFrame = 0;
	bombFrame = 0;
	bombImgIndex = bombFrame/BOMB_FRAME_NUM;
}

void Tank::worldTransform(SPoint &point)
{
	C2DMatrix mat;
	mat.Rotate(angleToArc(angle));
	mat.Translate(x, y);
	vector<SPoint> p;
	p.push_back(point);
	mat.TransformSPoints(p);
	point = p[0];
}

bool Tank::faceWall()
{
	SPoint pLeft = getUpLeftPoint(),pRight = getUpRightPoint();
	worldTransform(pLeft);
	worldTransform(pRight);
	if (!isPointInRect(&screen->clip_rect, pLeft.x, pLeft.y) || !isPointInRect(&screen->clip_rect, pRight.x, pRight.y))
	{
		return true;
	}

	return false;
}

bool Tank::faceOtherTank(const Tank *tank)
{
	if (!tank)
		return false;
	SPoint p1 = getUpLeftPoint(),p2 = getUpRightPoint();
	worldTransform(p1);
	worldTransform(p2);

	//contruct rect in tank's native coordinate
	SPoint p = tank->getDownLeftPoint();
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
	SPoint p[4];
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

void Tank::nativeTransform(SPoint &p) const
{
	C2DMatrix mat;
	mat.Translate(-x,-y);
	mat.Rotate(angleToArc(360-angle));
	vector<SPoint> pVec;
	pVec.push_back(p);
	mat.TransformSPoints(pVec);
	p = pVec[0];
}



void Tank::updateBullet()
{
	for (size_t i = 0; i < bulletVec.size(); ++i)
	{
		if (bulletVec[i])
		{
			bulletVec[i]->update();
			if (bulletVec[i]->checkDestory())
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
