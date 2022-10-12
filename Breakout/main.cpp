#include <SDL.h>
#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int TPS = 20;
	const int frameDelay = 1000 / FPS;
	const int tickDelay = 1000 / TPS;

	const int res = 10;

	Uint32 frameStart;
	int frameTime = 0;

	Uint32 tickStart;

	int tickTime;
	int pause = 0;

	game = new Game();
	//std::cout << " HEJ" << std::endl;
	game->init("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);
	//std::cout << " HEJ" << std::endl;
	int xpos = 0;
	Uint32 nextTick = 0;

	while (game->running())
	{

		frameStart = SDL_GetTicks();
		tickStart = SDL_GetTicks();

		game->handleEvents(&pause);
		game->update(frameTime);
		game->render();

		
		frameTime = SDL_GetTicks() - frameStart;
		//std::cout << frameDelay << std::endl;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		
	}

	game->clean();

	return 0;
}
