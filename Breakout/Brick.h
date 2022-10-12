#include <SDL.h>
#include "constants.h"
#pragma once
class Brick
{
protected:
	SDL_Rect body;
	SDL_Color clr;
	int brickType;
	
public:
	~Brick();
	int getX();
	int getY();
	int getW();
	int getH();
	SDL_Rect getBody();
	int Kill();
	virtual void render(SDL_Renderer* renderer);

};

