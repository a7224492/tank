#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include "game.h"

using namespace std;

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen = SDL_SetVideoMode(640, 480, 24, 0|SDL_SRCCOLORKEY|SDL_DOUBLEBUF);
	Game game(screen);
	bool running = true;
	Uint8 preTicks = 0,currTicks = 0;
	while (running)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		preTicks = currTicks;
		currTicks = SDL_GetTicks();
		int frameCount = (currTicks-preTicks)*0.06;
		for (int i = 0; i < currTicks-preTicks; ++i)
		{
			if (-1 == game.updateGame())
			{
				running = false;
				break;
			}		
		}	
		game.drawGame();
	}

	SDL_Quit();

	return 0;
}