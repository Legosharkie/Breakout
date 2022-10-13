#include <SDL.h>
#include <SDL_ttf.h>
#include "constants.h"
#pragma once
class Brick
{
protected:
	SDL_Rect body;
	SDL_Color clr;
	int brickType;
	int life;
	int maxLife;
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect textBox;
	TTF_Font* font;
	SDL_Renderer* renderer;
	
	
public:
	virtual ~Brick();
	int getX();
	int getY();
	int getW();
	int getH();
	int getLife();
	virtual void decreaseLife(){};
	SDL_Rect getBody();
	int getType();
	virtual void render(SDL_Renderer* renderer);

};

