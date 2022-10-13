#include <SDL.h>
#include "constants.h"
#pragma once
class Paddle
{
	public:
		Paddle();
		~Paddle();
		void move(int dir);
		int getX();
		int getY();
		int getW();
		int getH();
		void render(SDL_Renderer* renderer);

	private:
		SDL_Rect body;

};

