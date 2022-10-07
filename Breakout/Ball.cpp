#include "Ball.h"

Ball::Ball()
{
	vx = 10;
	vy = 5;
	body.x = SCREEN_WIDTH / 2;
	body.y = SCREEN_HEIGHT / 2;
	body.w = 50;
	body.h = 50;
}				  
Ball::~Ball()	  
{				  
				  
}				  
int  Ball::getX() 
{				  
	return body.x + body.w/2;	  
}				  
				  
int  Ball::getY() 
{				  
	return body.y + body.h/2;	  
}				  
				  
int  Ball::getR() 
{				  
	return body.w/2;	  
}				  
				  
void Ball::move() 
{
	body.x += vx;
	body.y += vy;
}

void Ball::collisionCheck(Paddle p)
{
	int xRight = body.x + body.w;
	int xLeft = body.x;
	int yTop = body.y;
	int yBottom = body.y + body.h;

	if (xRight >= SCREEN_WIDTH && vx > 0)
	{
		vx = -vx;
		body.x = SCREEN_WIDTH - body.w;
	}

	if (xLeft <= 0 && vx < 0)
	{
		vx = -vx;
		body.x = 0;
	}

	if (yTop <= 0 && vy < 0)
	{
		vy = -vy;
		body.y = 0;
	}

	if (yBottom >= SCREEN_HEIGHT && vy > 0)
	{
		vy = -vy;
		body.y = SCREEN_HEIGHT - body.h;
	}

	if (yBottom >= p.getY() && yBottom <= p.getY() + p.getH() && body.x >= p.getX() && body.x <= p.getX() + p.getW())
	{
		vy = -vy;
		body.y = p.getY() - body.h;
	}
}

void Ball::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &body);
}
