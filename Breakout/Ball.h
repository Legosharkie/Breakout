#include <SDL.h>
#include "constants.h"
#include "Paddle.h"
#include <vector>
#include "Brick.h"
#pragma once
class Ball
{
	public:
		Ball();
		~Ball();
		int getX();
		int getY();
		int getW();
		void move();
		void collisionWall(Paddle p);
		int collisionBrick(Brick b);
		void render(SDL_Renderer* renderer);
	private:
		int vx, vy;
		SDL_Rect body;

};

