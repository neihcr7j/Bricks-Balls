#include "level.h"

Level* Level::instance = nullptr;

void Level::decLevel()
{
  numberLevel = (numberLevel + levelMax - 1) % levelMax;
}
void Level::incLevel()
{
  numberLevel = (numberLevel + 1) % levelMax;
}
void Level::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);

  Draw::Rect(renderer, areaBackGround, backGroundColor);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(renderer, &areaBackClient);
  SDL_RenderFillRect(renderer, &areaDecLevel);
  SDL_RenderFillRect(renderer, &areaIncLevel);

  SDL_RenderPresent(renderer);
}
