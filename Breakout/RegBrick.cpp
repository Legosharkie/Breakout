#include "RegBrick.h"

RegBrick::RegBrick(int x, int y, int w, int h) 
{

	brickType = REG_BRICK;

	body.w = w;
	body.h = h;

	body.x = x;
	body.y = y;

	clr.r = 18;
	clr.g = 84;
	clr.b = 199;
	clr.a = SDL_ALPHA_OPAQUE;

}


void RegBrick::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
	SDL_RenderFillRect(renderer, &body);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, clr.a);
	SDL_RenderDrawRect(renderer, &body);
}