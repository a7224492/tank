#include "data.h"
#include "defs.h"

#define SET_IMG_DISPLAY_RGB(img, r,g,b)\
    SDL_Surface *temp = SDL_DisplayFormat(img);\
    SDL_FreeSurface(img);\
    img = temp;\
    SDL_SetColorKey(img, SDL_SRCCOLORKEY, SDL_MapRGB(img->format,r,g,b));

SDL_Surface *myTankImg  = NULL;
SDL_Surface *background = NULL;
SDL_Surface *bulletImg = NULL;

static void loadImg()
{
    if (!myTankImg)
    {
        myTankImg = SDL_LoadBMP(IMG_DIR"my_tank.bmp");
        SET_IMG_DISPLAY_RGB(myTankImg, 255,255,255);
    }
    if (!bulletImg)
    {
        bulletImg = SDL_LoadBMP(IMG_DIR"my_bullet.bmp");
        SET_IMG_DISPLAY_RGB(bulletImg, 0,0,0);
    }
    if (!background)
    {
        background = SDL_LoadBMP(IMG_DIR"tank_game_background.bmp");
        background = SDL_DisplayFormat(background);
    }
}

void initData()
{
    loadImg();
}

