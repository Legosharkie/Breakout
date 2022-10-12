#include "BallBrick.h"
#include <iostream>


BallBrick::BallBrick(int x, int y, int w, int h)
{
	brickType = 2;

	body.w = w;
	body.h = h;

	body.x = x;
	body.y = y;

	clr.r = 199;
	clr.g = 69;
	clr.b = 18;
	clr.a = SDL_ALPHA_OPAQUE;

}

void BallBrick::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
	SDL_RenderFillRect(renderer, &body);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, clr.a);
	SDL_RenderDrawRect(renderer, &body);
}