#include "Game.h"

Game::Game()
{
	player = Paddle();
	std::cout << "HELLO FROM GAME!" << std::endl;
	//balls.push_back(new Ball());
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


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		TTF_Init();
		std::cout << "Initializing..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		//SDL_GetWindowSize(window, &windowW, &windowH);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_RenderSetVSync(renderer, 1);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
			font = TTF_OpenFont("arial.ttf", 25);
		}

		isRunning = true;
		
		rows = 17;
		N_per_row = 40;
		blockHeight = 30;
		minLen = SCREEN_WIDTH / N_per_row;

		initBricks(rows, blockHeight, N_per_row, minLen);
	}
	else
	{
		isRunning = false;
	}
}

void Game::handleEvents(int *pause)
{
	SDL_Event event;

	//SDL_WaitEvent(&event);
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
	
	int fps =(int) (1000.0 / dt);
	//std::cout << fps << std::endl;
	surface = TTF_RenderText_Solid(font, std::to_string(fps).c_str(), { 255, 255, 255 });
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	int texW, texH;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	FPS_box.w = texW;
	FPS_box.h = texH;

	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	player.move(-keystates[SDL_SCANCODE_A] + keystates[SDL_SCANCODE_D]);

	Ball* ball;
	for (int i = balls.size()-1; i >= 0; i--)
	{
		int state = 0;
		ball = balls[i];
		Brick* collisionBrick = nullptr;
		int brickIdx;
		for (brickIdx = bricks.size() - 1; brickIdx >= 0; brickIdx--)
		{
			if (ball->collisionBrick(*bricks[brickIdx], &state))
			{
				collisionBrick = bricks[brickIdx];
				break;
			}
		}
		//std::cout << state << std::endl;
		
		ball->move(collisionBrick, state);
		ball->collisionWall(player);

		if (ball->isDead())
		{
			delete balls[i];
			balls.erase(balls.begin() + i);
			//std::cout << "There are now " << balls.size() << " balls" << std::endl;
		}

		if (collisionBrick)
		{
			// death effects
			collisionBrick->decreaseLife();
			if (collisionBrick->getLife() == 0)
			{
				int brickType = collisionBrick->getType();
				switch (brickType)
				{
				case REG_BRICK:
					break;

				case BALL_BRICK:
					balls.push_back( new Ball(collisionBrick->getX() + collisionBrick->getW() / 2, collisionBrick->getY() + collisionBrick->getH() / 2, 10, -10) );
					balls.push_back( new Ball(collisionBrick->getX() + collisionBrick->getW() / 2, collisionBrick->getY() + collisionBrick->getH() / 2, -10, -10) );
					break;
				}

				delete bricks[brickIdx];
				bricks.erase(bricks.begin() + brickIdx);
				//std::cout << "There are now " << bricks.size() << " bricks remaining" << std::endl;
			}
		}
		
	}
	
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 34, 41, 69, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	player.render(renderer);
	for (auto &ball : balls)
		ball->render(renderer);
		
	for (auto &brick : bricks)
		brick->render(renderer);

	SDL_RenderCopy(renderer, texture, NULL, &FPS_box);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}


void Game::mousePress(SDL_MouseButtonEvent& b)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (b.button == SDL_BUTTON_LEFT)
		balls.push_back(new Ball(x,y,4,4));
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
		//std::cout << newSize << std::endl;
	}
	chunks.push_back(length);
	return chunks;
}

void Game::initBricks(int rows, int blockHeight, int N_per_row, int minLen)
{
	std::vector<int>chunks;
	int nextX;
	double randNum;
	int yoff = 3;

	for (int i = yoff; i < rows+yoff; i++)
	{
		chunks = getChunks(SCREEN_WIDTH, N_per_row, minLen);
		nextX = 0;
		for (int j = 0; j < chunks.size(); j++)
		{
			randNum = ((double)rand() / RAND_MAX);
			if (randNum < 1) 
			{
				bricks.push_back(new BallBrick(nextX, i * blockHeight, chunks[j], blockHeight, font, renderer));
				
			}
			else
				bricks.push_back(new RegBrick(nextX, i * blockHeight, chunks[j], blockHeight, font, renderer));
			nextX += chunks[j];

		}
	}
	chunks.clear();
}

void Game::reset()
{
	for (int i = 0; i < balls.size(); i++)
	{
		delete balls[i];
	}
	balls.clear();
	balls.reserve(1);

	for (int i = 0; i < bricks.size(); i++)
	{
		delete bricks[i];
	}
	bricks.clear();
	bricks.reserve(1);
	
	initBricks(rows, blockHeight, N_per_row, minLen);

	//balls.push_back(new Ball());
	//player = Paddle();

}
