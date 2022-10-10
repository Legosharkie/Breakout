#include "Brick.h"
#include <cstdlib>
#include <iostream>

Brick::Brick(int x, int y, int w, int h)
{
	body.w = w;
	body.h = h;

	body.x = x;
	body.y = y;

	int max = 2;
	int min = 0;
	
	int randNum = rand() % (max - min + 1) + min;
	//std::cout << randNum << std::endl;
	int rgb[3];
	
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;

	rgb[randNum] = 255;
	


	clr.r = rgb[0];
	clr.g = rgb[1];
	clr.b = rgb[2];
	clr.a = SDL_ALPHA_OPAQUE;

	//std::cout << clr.r << std::endl;
}

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