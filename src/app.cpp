#include "app.hpp"

constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;
constexpr Uint32 framerate = 60;
const char *kWindowTitle = "Game of Life";

App::App()
{
	if (Init())
	{
		isRunning_ = true;
		srand(time(NULL));
		world = new World(kWindowWidth / 32, kWindowHeight / 32, 32);
	}
}

App::~App()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

bool App::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		window_ = SDL_CreateWindow(kWindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight, 0);
		if (window_ != nullptr)
		{
			renderer_ = SDL_CreateRenderer(window_, -1, 0);
		}
		else
		{
			std::cout << "An error has ocurred: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "An error has ocurred: " << SDL_GetError() << std::endl;
		return false;
	}

	std::cout << "SDL Initialized." << std::endl;
	return true;
}

void App::HandleEvents()
{
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning_ = false;
			break;
		default:
			break;
		}
	}
}

void App::Update()
{
	world->Update();
}

void App::Render()
{
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 1);
	SDL_RenderClear(renderer_);
	world->Render(renderer_);
	SDL_RenderPresent(renderer_);
}

void App::Run()
{
	Uint32 time_step_ms = 1000 / framerate;
	Uint32 next_step = SDL_GetTicks();
	while (isRunning_)
	{
		Uint32 now = SDL_GetTicks();
		if (next_step <= now)
		{
			int limit = 10; // minimum framerate
			while ((next_step <= now) && (limit--))
			{
				HandleEvents();
				Update();
				next_step += time_step_ms;
			}
			Render();
		}
		else
		{
			SDL_Delay(SDL_GetTicks() - now);
		}
	}
}