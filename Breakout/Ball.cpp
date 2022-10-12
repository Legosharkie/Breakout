#include "Ball.h"
#include <vector>
#include "Brick.h"
#include <iostream>

Ball::Ball()
{
	vx = 200;
	vy = 200;
	body.x = SCREEN_WIDTH / 2;
	body.y = SCREEN_HEIGHT - 200;
	body.w = 20;
	body.h = 20;
}				  
Ball::Ball(int x, int y, int vx, int vy)
{
	body.w = 20;
	body.h = 20;

	//this->vx = vx;
	//this->vy = vy;
	this->vx = vx;
	this->vy = vy;

	body.x = x - body.w / 2;
	body.y = y - body.h / 2;
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
				  
void Ball::move(double dt)
{
	dt = dt / 1000;
	std::cout << dt << std::endl;
	body.x += vx*dt;
	body.y += vy*dt;
}

int Ball::collisionBrick(Brick b)
{
	int ret = 0;
	SDL_Rect* overlap = new SDL_Rect();
	SDL_Rect brickBody = b.getBody();

	int xRight, xLeft, yTop, yBot;

	xRight = body.x + body.w;
	xLeft = body.x;
	yTop = body.y;
	yBot = body.y + body.h;

	int x, y;
	x = (brickBody.x + (brickBody.w / 2)) - (body.x + (body.w / 2));
	y = (brickBody.y + (brickBody.h / 2)) - (body.y + (body.h / 2));

	
	if (body.x + body.w + vx > brickBody.x &&
		body.x + vx < brickBody.x + brickBody.w &&
		body.y + body.h > brickBody.y &&
		body.y < brickBody.y + brickBody.h)
	{
		vx *= -1;
		ret = 1;
	}


	if (body.x + body.w > brickBody.x &&
		body.x < brickBody.x + brickBody.w &&
		body.y + body.h + vy > brickBody.y &&
		body.y + vy < brickBody.y + brickBody.h)
	{
		vy *= -1;
		ret = 1;
		
	}
	
	return ret;
}

bool Ball::isDead()
{
	// bottom delete
	if (body.y >= SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
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
	SDL_RenderFillRectF(renderer, &body);
}
