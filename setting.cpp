#include "setting.h"

Setting* Setting::instance = nullptr;

void Setting::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);

  Draw::Rect(renderer, areaBackGround, backGroundColor);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(renderer, &areaBackClient);

  SDL_RenderPresent(renderer);
}
