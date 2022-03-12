#include "game.h"

Game* Game::instance = nullptr;

bool Game::init(std::string TITLE, int width, int height)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    Log::SDLError(std::cout, "SDL init fail");
    return 0;
  }

  window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (window == nullptr)
  {
    Log::SDLError(std::cout, "window init fail");
    return 0;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == nullptr)
  {
    Log::SDLError(std::cout, "renderer init fail");
    return 0;
  }

  bRunning = 1;

  return 1;
}

bool Game::running()
{
  return bRunning;
}

double Game::timeForOneFrame()
{
  return (double)1000 / FPS;
}

void Game::quit()
{
  bRunning = 0;
}

void Game::cleaner()
{
  Log::Notification(std::cout, "Cleaning game....");
  SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
