#include "BallBrick.h"
#include <iostream>


BallBrick::BallBrick(int x, int y, int w, int h, TTF_Font* font, SDL_Renderer* renderer)
{
	brickType = BALL_BRICK;
	maxLife = 1;
	life = maxLife;
	this->renderer = renderer;

	body.w = w;
	body.h = h;

	body.x = x;
	body.y = y;

	clr.r = 199;
	clr.g = 69;
	clr.b = 18;
	clr.a = SDL_ALPHA_OPAQUE;

	// Text
	this->font = font;
	surface = TTF_RenderText_Solid(font, std::to_string(life).c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	textBox = { 0, 0, texW, texH };
	textBox.x = body.x + body.w / 2 - textBox.w / 2;
	textBox.y = body.y + body.h / 2 - textBox.h / 2;
}

BallBrick::~BallBrick()
{
	SDL_DestroyTexture(texture);
	//SDL_FreeSurface(surface);
}


void BallBrick::decreaseLife()
{
	life--;
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font, std::to_string(life).c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	//SDL_UpdateTexture(texture, &textBox, surface->pixels, surface->pitch);
	SDL_FreeSurface(surface);
}

void BallBrick::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
	SDL_RenderFillRect(renderer, &body);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, clr.a);
	SDL_RenderDrawRect(renderer, &body);

	SDL_RenderCopy(renderer, texture, NULL, &textBox);
}