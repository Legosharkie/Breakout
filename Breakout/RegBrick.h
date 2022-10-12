#include "Ball.h"
#include "Brick.h"
#pragma once
class RegBrick : public Brick
{

	public:
		RegBrick(int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* renderer);
		~RegBrick();
		void decreaseLife();
		void render(SDL_Renderer* renderer);

};

