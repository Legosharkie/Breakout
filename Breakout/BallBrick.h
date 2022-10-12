#pragma once
#include "Brick.h"
#include "Ball.h"
class BallBrick : public Brick
{
	public: 
		BallBrick(int x, int y, int w, int h);
		~BallBrick();
		void render(SDL_Renderer* renderer);
};

