#include "ResourceManager.h"
#include "utils.h"
#include <string>
#include <SDL/SDL_rotozoom.h>

#ifdef _WIN32
#define RESOURCE_PATH "E:/github_code/tank/"
#else
#define RESOURCE_PATH "/mnt/share/tank/"
#endif

#define BULLET_BOMB_IMG_NUM 17

ResourceManager* ResourceManager::getInstance()
{
	static ResourceManager rm;
	return &rm;
}

void ResourceManager::loadData()
{
	for (int i = 0; i < BULLET_BOMB_IMG_NUM; ++i){
		std::string imgFile = RESOURCE_PATH"gfx/bomb/BulletBomb/"+itos(10015+i)+".png";
		SDL_Surface *img = IMG_Load(imgFile.c_str());
		m_vecBulletBombEffectImg.push_back(rotozoomSurface(img, 0, 0.4, SMOOTHING_ON));
	}

    string ttfStr = RESOURCE_PATH"ttf/tuffy_bold.ttf";
    m_pNormalFont = TTF_OpenFont(ttfStr.c_str(), 10);
}

ResourceManager::~ResourceManager()
{

}
