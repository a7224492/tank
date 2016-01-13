#include <stdio.h>
#include <SDL/SDL.h>
#include "defs.h"
#include "data.h"
#include "draw.h"
#include "tank.h"
#include "events.h"
#include "bfield.h"

extern SDL_Surface *background;

MyTank myTank;
EnemyTank enemyTank[3];
SDL_Surface *screen;

int main(int arc, char **argv)
{
    int i;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_InitSubSystem( SDL_INIT_AUDIO);
    SDL_SetVideoMode( 640, 480,16,
                           0 | SDL_HWSURFACE | SDL_DOUBLEBUF );
    screen = SDL_GetVideoSurface();
    initData();
    initMyTank(&myTank, 0, 0);
    for (i = 0; i < 3; ++i)
    {
        initEnemyTank(&enemyTank[i], 100+100*i, 100);
    }
    initBfield();

    int running = 1;
    Uint8 *keystate;
    int inputDelay = 0;
    int currTicks, preTicks, ms;
    while (running)
    {
        //Pause
        SDL_Delay(20);
        preTicks = currTicks;
        currTicks = SDL_GetTicks();
        ms = currTicks-preTicks;

        updateGame(ms);
        drawGame();

        SDL_PumpEvents();

        keystate = SDL_GetKeyState(0);

        if (inputDelay > 0)
            continue;

        if (keystate[SDLK_ESCAPE])
        {
            running = 0;
        }

        setMyTankKeyEvent(keystate);
    }
    SDL_Quit();

    return  1 ;
}
