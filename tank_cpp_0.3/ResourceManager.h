#ifndef RESOURECEMANAGER_H
#define RESOURECEMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <vector>

class ResourceManager
{
public:
	static ResourceManager* getInstance();
	void loadData();

	const std::vector<SDL_Surface *>& getBulletBombEffectImg() const {
		return m_vecBulletBombEffectImg;
	}

	const TTF_Font* getNormalFont() const{
		return m_pNormalFont;	
	}

	~ResourceManager();
private:
	ResourceManager(){};
	ResourceManager(const ResourceManager &);
	ResourceManager& operator= (const ResourceManager &);

	std::vector<SDL_Surface*> m_vecBulletBombEffectImg;
	TTF_Font *m_pNormalFont;
};

#define resourceMgr ResourceManager::getInstance()

#endif
