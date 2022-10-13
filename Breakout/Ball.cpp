#include "Ball.h"
#include <vector>
#include "Brick.h"
#include <iostream>

Ball::Ball()
{
	vx = 10;
	vy = 10;
	body.x = SCREEN_WIDTH / 2;
	body.y = SCREEN_HEIGHT - 200;
	body.w = 10;
	body.h = 10;

	overlap = { 0,0,0,0 };
}				  
Ball::Ball(int x, int y, int vx, int vy)
{
	body.w = 10;
	body.h = 10;

	//this->vx = vx;
	//this->vy = vy;
	this->vx = vx;
	this->vy = vy;

	body.x = x - body.w / 2;
	body.y = y - body.h / 2;

	overlap = { 0,0,0,0 };
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
				  
void Ball::move(Brick* brick, int state)
{
	if (state == 0)
	{
		body.x += vx;
		body.y += vy;
	}
	else
	{
		switch (state)
		{
		case 1:
			body.x = brick->getX() - body.w;
			vx *= -1;
			break;
		case 2:
			body.x = brick->getX() + brick->getW();
			vx *= -1;
			break;
		case 3:
			body.y = brick->getY() - body.h;
			vy *= -1;
			break;
		case 4:
			body.y = brick->getY() + brick->getH();
			vy *= -1;
			break;

		}
		return;
	}
}

int Ball::collisionBrick(Brick b, int* state)
{
	int ret = 0;
	*state = 0;
	//SDL_Rect* overlap = new SDL_Rect();
	SDL_Rect blockBody = b.getBody();
	SDL_Rect collisionX = { body.x + vx, body.y, body.w, body.h };
	SDL_Rect collisionY = { body.x, body.y + vy, body.w, body.h };

	// x collision
	if (SDL_IntersectRect(&collisionX, &blockBody, &overlap))
	{
		if (body.x + body.w <= blockBody.x)
			*state = 1;
		else if (body.x >= blockBody.x + blockBody.w)
			*state = 2;
		
		//vx *= -1;
		ret = 1;
	}

	// y collision
	if (SDL_IntersectRect(&collisionY, &blockBody, &overlap))
	{
		
		if (body.y + body.h <= blockBody.y)
		{
			*state = 3;
			
		}
		else if (body.y >= blockBody.y + blockBody.h)
			*state = 4;
		
		//vy *= -1;
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
	SDL_RenderFillRect(renderer, &body);
}
