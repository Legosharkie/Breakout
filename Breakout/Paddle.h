#include <SDL.h>
#include "constants.h"
#pragma once
class Paddle
{
	public:
		Paddle();
		~Paddle();
		void move(int dir);
		void render(SDL_Renderer* renderer);

	private:
		SDL_Rect body;
		int x, y;
};

