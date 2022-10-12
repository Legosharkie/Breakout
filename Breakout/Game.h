#include <SDL.h>
#include <iostream>
#include <vector>
#include <string>
#include "Paddle.h"
#include "Ball.h"
#include "constants.h"
#include "BallBrick.h"
#include "RegBrick.h"
#pragma once
class Game
{
	public:
		Game();
		~Game();

		void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
		
		void handleEvents(int* pause);
		void update(double dt);
		void render();
		void clean();
		void reset();
		void initBricks(int rows, int blockHeight, int N_per_row, int minLen);
		bool running() { return isRunning; }
		std::vector<int> getChunks(int length, int N_chunks, int minLen);
		void mousePress(SDL_MouseButtonEvent& b);

	private:
		int count = 0;
		int windowH, windowW, windowRes, aspectRatio; 
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		Paddle player;
		Ball ball;
		TTF_Font* font;
		SDL_Rect FPS_box;
		std::vector<Brick*> bricks;
		std::vector<Ball*> balls;
		SDL_Surface* surface;
		SDL_Texture* texture;

		int N_per_row, blockHeight, rows, minLen;


};

