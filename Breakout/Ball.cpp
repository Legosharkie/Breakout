#include "Ball.h"
#include <vector>
#include "Brick.h"
#include <iostream>

Ball::Ball()
{
	vx = 10;
	vy = 5;
	body.x = SCREEN_WIDTH / 2;
	body.y = SCREEN_HEIGHT - 200;
	body.w = 20;
	body.h = 20;
}				  
Ball::~Ball()	  
{				  
				  
}				  
int  Ball::getX() 
{				  
	return body.x;	  
}				  
				  
int  Ball::getY() 
{				  
	return body.y;	  
}				  
				  
int  Ball::getW() 
{				  
	return body.w;	  
}				  
				  
void Ball::move()
{
	body.x += vx;
	body.y += vy;
}

int Ball::collisionBrick(Brick b)
{
	int hit = 0;

	int xRight = body.x + body.w;
	int xLeft = body.x;
	int yTop = body.y;
	int yBottom = body.y + body.h;

	// right brick bounce
	
	if (xRight >= b.getX() && xRight <= b.getX() + b.getW() && vx > 0 && ((yTop > b.getY() && yTop < b.getY() + b.getH()) || ((yBottom > b.getY() && yBottom < b.getY() + b.getH()))))
	{
		std::cout << "Right bounce" << std::endl;
		vx = -vx;
		body.x = b.getX() - body.w;
		hit = 1;

		xRight = body.x + body.w;
		xLeft = body.x;
		yTop = body.y;
		yBottom = body.y + body.h;
	}
	

	
	// left brick bounce
	if (xLeft <= b.getX()+b.getW() && xLeft >= b.getX() && vx < 0 && ((yTop > b.getY() && yTop < b.getY() + b.getH()) || ((yBottom > b.getY() && yBottom < b.getY() + b.getH()))))
	{
		std::cout << "Left bounce" << std::endl;
		vx = -vx;
		body.x = b.getX() + b.getW();
		hit = 1;
		xRight = body.x + body.w;
		xLeft = body.x;
		yTop = body.y;
		yBottom = body.y + body.h;
	}
	

	// roof bounce
	if (yTop <= b.getY() + b.getH() && yTop >= b.getY() && vy < 0 && ((xRight >= b.getX() && xRight <= b.getX() + b.getW()) || ((xLeft >= b.getX() && xLeft <= b.getX() + b.getW()))))
	{
		std::cout << "Top bounce" << std::endl;
		vy = -vy;
		body.y = b.getY() + b.getH();
		hit = 1;
		xRight = body.x + body.w;
		xLeft = body.x;
		yTop = body.y;
		yBottom = body.y + body.h;
	}

	
	// bottom bounce
	if (yBottom >= b.getY() && yBottom <= b.getY() + b.getH() && vy > 0 && ((xRight >= b.getX() && xRight <= b.getX() + b.getW()) || ((xLeft >= b.getX() && xLeft <= b.getX() + b.getW()))))
	{
		std::cout << "Bottom bounce" << std::endl;
		vy = -vy;
		body.y = b.getY()-b.getH();
		hit = 1;

		xRight = body.x + body.w;
		xLeft = body.x;
		yTop = body.y;
		yBottom = body.y + body.h;
	}
	
	return hit;
}

void Ball::collisionWall(Paddle p)
{
	int xRight = body.x + body.w;
	int xLeft = body.x;
	int yTop = body.y;
	int yBottom = body.y + body.h;

	// right wall bounce
	if (xRight >= SCREEN_WIDTH && vx > 0)
	{
		vx = -vx;
		body.x = SCREEN_WIDTH - body.w;
	}

	// left wall bounce
	if (xLeft <= 0 && vx < 0)
	{
		vx = -vx;
		body.x = 0;
	}

	// roof bounce
	if (yTop <= 0 && vy < 0)
	{
		vy = -vy;
		body.y = 0;
	}

	/*
	// bottom bounce
	if (yBottom >= SCREEN_HEIGHT && vy > 0)
	{
		vy = -vy;
		body.y = SCREEN_HEIGHT - body.h;
	}
	*/

	// bounce on paddle
	if (yBottom >= p.getY() && yBottom <= p.getY() + p.getH() && body.x >= p.getX() && body.x <= p.getX() + p.getW())
	{
		vy = -vy;
		body.y = p.getY() - body.h;
	}

	// left side of paddle
	if (xRight >= p.getX() && xRight <= p.getX() + p.getW() && ((yTop > p.getY() && yTop <= p.getY()+p.getH()) || (yBottom > p.getY() && yBottom <= p.getY() + p.getH())))
	{
		vx = -vx;
		body.x = p.getX() - body.w;
	}

	// right side of paddle
	if (xLeft <= p.getX() + p.getW() && xLeft >= p.getX() && ((yTop > p.getY() && yTop <= p.getY() + p.getH()) || (yBottom > p.getY() && yBottom <= p.getY() + p.getH())))
	{
		vx = -vx;
		body.x = p.getX() + p.getW();
	}
}

void Ball::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &body);
}
