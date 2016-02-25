#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include <SDL/SDL_ttf.h>
#include "game.h"
#include "Vector2D.h"

using namespace std;

int main(int argc, char **argv)
{
    Vector2D v1(5,5);
    Vector2D v2(1,0);

    Vector2D v = sinVector(v1, v2);
	cout << v.x << " " << v.y << endl;
//	SDL_Init(SDL_INIT_EVERYTHING);
//    TTF_Init();
//    SDL_Surface *screen = SDL_SetVideoMode(640, 480, 24, 0|SDL_SRCCOLORKEY|SDL_DOUBLEBUF);
//	Game game(screen);
//	bool running = true;
//	double preTicks = 0,currTicks = 0;
//
//	while (running)
//	{
//		SDL_Event event;
//		SDL_PollEvent(&event);
//		if (event.type == SDL_QUIT)
//		{
//			running = false;
//		}
//		preTicks = currTicks;
//		currTicks = SDL_GetTicks();
//		double elapsedTime = currTicks-preTicks;
//
//		game.setElapsedTime(elapsedTime);
//		if (-1 == game.updateGame(elapsedTime))
//		{
//			running = false;
//			break;
//		}
//
//		game.drawGame();
//	}
//
//	SDL_Quit();
//
//	return 0;
}
