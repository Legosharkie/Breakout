#include "Game.h"

Game::Game()
{
	player = Paddle();
	balls.push_back(new Ball());
}

Game::~Game()
{

}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen)
{
	int flags = 0;
	
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// random seed 
	srand(time(NULL));

	//windowRes = res;
	aspectRatio = (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT;

	initBricks(5, 30, 10, SCREEN_WIDTH / 10);

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initializing..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		//SDL_GetWindowSize(window, &windowW, &windowH);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Game::handleEvents(int *pause)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	//const Uint8* state = SDL_GetKeyboardState(NULL);

	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			mousePress(event.button);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_p)
			{
				*pause = !(*pause);
				break;
			}

			if (event.key.keysym.sym == SDLK_r)
			{
				reset();
			}
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		
		default:
			break;
	}
}
 
void Game::update(double dt)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	player.move(-keystates[SDL_SCANCODE_A] + keystates[SDL_SCANCODE_D]);
	Ball* ball;
	for (int i = balls.size()-1; i >= 0; i--)
	{
		ball = balls[i];
		ball->move(dt);
		ball->collisionWall(player);

		if (ball->isDead())
		{
			delete balls[i];
			balls.erase(balls.begin() + i);
		}

		for (int j = bricks.size() - 1; j >= 0; j--)
		{
			if (ball->collisionBrick(*bricks[j]))
			{
				delete bricks[j];
				bricks.erase(bricks.begin() + j);
				std::cout << bricks.size() << std::endl;
			}
		}
	}
	
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 34, 41, 69, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	
	player.render(renderer);
	for (auto ball : balls)
		ball->render(renderer);
		
	for (auto brick : bricks)
		brick->render(renderer);


	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void Game::mousePress(SDL_MouseButtonEvent& b)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (b.button == SDL_BUTTON_LEFT)
		balls.push_back(new Ball(x,y,400,400));
}

std::vector<int> Game::getChunks(int length, int N_chunks, int minLen)
{
	std::vector<int> chunks;
	int maxLen;
	int newSize;
	for (int i = 0; i < N_chunks-1; i++)
	{
		maxLen = std::ceill(length/(N_chunks - chunks.size()));
		newSize = rand() % (maxLen - minLen + 1) + minLen;
		length = length - newSize;
		chunks.push_back(newSize);
	}
	chunks.push_back(length);
	return chunks;
}

void Game::initBricks(int rows, int blockHeight, int N_per_row, int minLen)
{
	std::vector<int>chunks;
	int nextX;
	double randNum;
	int yoff = 4;

	for (int i = yoff; i < rows+yoff; i++)
	{
		chunks = getChunks(SCREEN_WIDTH, N_per_row, minLen);
		nextX = 0;
		for (int j = 0; j < chunks.size(); j++)
		{
			randNum = ((double)rand() / RAND_MAX);
			if (randNum <= 0.1) 
			{
				bricks.push_back(new BallBrick(nextX, i * blockHeight, chunks[j], blockHeight));
				
			}
			else
				bricks.push_back(new RegBrick(nextX, i * blockHeight, chunks[j], blockHeight));
			nextX += chunks[j];

		}
	}

}

void Game::reset()
{

	balls.clear();
	bricks.clear();
	initBricks(5, 30, 10, SCREEN_WIDTH / 10);

	//balls.push_back(new Ball());
	//player = Paddle();

}
