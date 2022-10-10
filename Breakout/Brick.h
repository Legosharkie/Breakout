#include <SDL.h>
#include "constants.h"
#pragma once
class Brick
{
	public:
		Brick(int x, int y, int w, int h);
		~Brick();
		int getX();
		int getY();
		int getW();
		int getH();
		void Hit();
		void render(SDL_Renderer* renderer);

	private:
		SDL_Rect body;
		SDL_Color clr;
};

