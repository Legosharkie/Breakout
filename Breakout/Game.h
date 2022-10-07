#include <SDL.h>
#include <iostream>
#include <vector>
#include "Paddle.h"
#include "constants.h"
#pragma once
class Game
{
	public:
		Game();
		~Game();

		void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
		
		void handleEvents(int* pause);
		void update();
		void render();
		void clean();
		bool running() { return isRunning; }
		void mousePress(SDL_MouseButtonEvent& b);

	private:
		int count = 0;
		int windowH, windowW, windowRes, aspectRatio; 
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		Paddle player;


};

