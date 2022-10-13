#pragma once
#include "Brick.h"
#include "Ball.h"
class BallBrick : public Brick
{
	public: 
		BallBrick(int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* renderer);
		~BallBrick();
		void decreaseLife();
		void render(SDL_Renderer* renderer);
};

