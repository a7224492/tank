#include "ResourceManager.h"
#include "utils.h"
#include <string>
#include <SDL/SDL_rotozoom.h>

#define IMG_PATH "E:/github_code/tank/gfx/"

#define BULLET_BOMB_IMG_NUM 17

ResourceManager* ResourceManager::getInstance()
{
	static ResourceManager rm;
	return &rm;
}

void ResourceManager::loadData()
{
	for (int i = 0; i < BULLET_BOMB_IMG_NUM; ++i){
		std::string imgFile = IMG_PATH"bomb/BulletBomb/"+itos(10015+i)+".png";
		SDL_Surface *img = IMG_Load(imgFile.c_str());
		m_vecBulletBombEffectImg.push_back(rotozoomSurface(img, 0, 0.4, SMOOTHING_ON));
	}
}

ResourceManager::~ResourceManager()
{

}