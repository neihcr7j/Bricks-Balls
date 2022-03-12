#include "clientGame.h"

clientGame* clientGame::instance = nullptr;

void clientGame::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);

  Draw::Rect(renderer, areaBackGround, backGroundColor);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(renderer, &areaPlay);
  SDL_RenderFillRect(renderer, &areaLevel);
  SDL_RenderFillRect(renderer, &areaSetting);


  SDL_SetRenderDrawColor(renderer, detailColor(backGroundColor));
  SDL_RenderPresent(renderer);
}
