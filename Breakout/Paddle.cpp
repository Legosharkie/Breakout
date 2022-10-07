#include "Paddle.h"

Paddle::Paddle()
{
	body.w = 400;
	body.h = 20;

	body.x = SCREEN_WIDTH/2 - body.w/2;
	body.y = SCREEN_HEIGHT - body.h*5;
}

Paddle::~Paddle()
{

}

void Paddle::move(int dir)
{
	int speed = 20;
	body.x += dir * speed;
}

int Paddle::getX()
{
	return body.x;
}

int Paddle::getY()
{
	return body.y;
}

int Paddle::getW()
{
	return body.w;
}

int Paddle::getH()
{
	return body.h;
}

void Paddle::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &body);
}