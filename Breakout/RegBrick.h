#include "Ball.h"
#include "Brick.h"
#pragma once
class RegBrick : public Brick
{
	public:
		RegBrick(int x, int y, int w, int h);
		~RegBrick();
		void render(SDL_Renderer* renderer);

};

