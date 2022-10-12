#include "Brick.h"
#include <cstdlib>
#include <iostream>

Brick::~Brick()
{

}

void Brick::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
	SDL_RenderFillRect(renderer, &body);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, clr.a);
	SDL_RenderDrawRect(renderer, &body);
}

int Brick::getType()
{
	return brickType;
}

int Brick::getX()
{
	return body.x;
}

int Brick::getY()
{
	return body.y;
}

int Brick::getW()
{
	return body.w;
}

int Brick::getH()
{
	return body.h;
}

SDL_Rect Brick::getBody()
{
	return body;
}