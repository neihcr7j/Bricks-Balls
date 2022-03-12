#include "parameter.h"

//SDL_Texture *Texture[300];
//int sz = 0;

void unitize(double &x, double &y)
{
  double l = sqrt(x * x + y * y);
  x /= l;
  y /= l;
}

//========================================================================================================================//

void Log::Notification(std::ostream& os, const std::string &msg)
{
  os << msg << std::endl;
}

void Log::SDLError(std::ostream& os, const std::string &msg)
{
  os << msg << " Error: " << SDL_GetError() << std::endl;
}

void Log::Warning(std::ostream& os, const std::string &msg)
{
  os << "Warning: " << msg << std::endl;
}

//========================================================================================================================//

int Get::xMiddleBar()
{
  SDL_PumpEvents();
  int x, y;
  SDL_GetMouseState(&x, &y);
  x = std::max(x, widthBar / 2);
  x = std::min(x, WIDTH - widthBar / 2);
  return x;
}

SDL_Rect Get::Bar(double x)
{
  SDL_Rect r = {x - widthBar / 2, yBar, widthBar, heightBar};
  r.x = std::max(r.x, 0);
  r.x = std::min(r.x, WIDTH - widthBar);
  return r;
}

double Get::Angle(double x, double y)
{
  double alpha = atan(y / x);
  if (y == 0)
    alpha = (x >= 0 ? 0 : PI);
  else
  if (y > 0)
    alpha = (alpha > 0 ? alpha : alpha + PI);
  else
    alpha = (alpha > 0 ? alpha + PI : alpha);

  return alpha;
}

//========================================================================================================================//

bool Check::clickInRect(SDL_MouseButtonEvent e, const SDL_Rect& r)
{
  return e.x >= r.x && e.y >= r.y && e.x <= r.x + r.w && e.y <= r.y + r.h;
}

//========================================================================================================================//

void Draw::Rect(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c)
{
  SDL_SetRenderDrawColor(renderer, detailColor(c));
  SDL_RenderFillRect(renderer, &r);
}

void Draw::Cell(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c)
{
  int d = r.w / 10;
  r.x += d; r.y += d;
  r.w -= 3 * d; r.h -= 3 * d;
  Rect(renderer, r, c);
}

void Draw::Image(SDL_Renderer *renderer, SDL_Rect r, std::string path)
{
  SDL_Surface *image = IMG_Load(path.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  SDL_RenderCopy(renderer, texture, NULL, &r);
//  Texture[sz++] = texture;
}

void Draw::Bar(SDL_Renderer *renderer, double x)
{
  Rect(renderer, Get::Bar(x), ORANGE);
}

void Draw::destroyImage()
{
//  for (int i = 0; i < sz; ++i)
//    SDL_DestroyTexture(Texture[i]);
//  sz = 0;
}

