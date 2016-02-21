#include "BombEffect.h"

#define FRAME_PERIOD 15

BombEffect::BombEffect() : 
  m_vPos(0,0)
, m_iFrame(0)
, m_bFinish(false)
{

}

void BombEffect::update()
{
	m_iFrame += 1;
	if ((m_iFrame / FRAME_PERIOD) == m_vecBombImg.size())
	{
		m_bFinish = true;
	}
}

void BombEffect::draw(SDL_Surface *screen)
{
	if (!m_bFinish)
	{
		int imgIndex = m_iFrame / FRAME_PERIOD;
		SDL_Rect rect = { m_vPos.x - m_vecBombImg[imgIndex]->w / 2, m_vPos.y - m_vecBombImg[imgIndex]->h / 2, 0, 0 };
 		SDL_BlitSurface(m_vecBombImg[imgIndex], 0, screen, &rect);
	}
}