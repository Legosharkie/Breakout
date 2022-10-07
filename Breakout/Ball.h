#include <SDL.h>
#include "constants.h"
#include "Paddle.h"
#pragma once
class Ball
{
	public:
		Ball();
		~Ball();
		int getX();
		int getY();
		int getR();
		void move();
		void collisionCheck(Paddle p);
		void render(SDL_Renderer* renderer);
	private:
		int vx, vy;
		SDL_Rect body;

};

