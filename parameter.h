#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <fstream>
#include <math.h>

#include <vector>
#include <queue>
#include <stack>

#include <SDL.h>
#include <SDL_image.h>

#define detailColor(c) c.r, c.g, c.b, c.a

const double PI = 3.1415926535;

const std::string TITLE = "Bricks&Balls";
const int WIDTH = 510;
const int HEIGHT = 700;

const int lCell = 10;

const int rBall = lCell / 2 - 1;

const int rGift = lCell;

const int widthBar = WIDTH / 3;
const int heightBar = rBall * 5;
const int yBar = HEIGHT - HEIGHT / 20 + rBall;

const SDL_Rect areaBackGround = {0, 0, WIDTH, HEIGHT};

const SDL_Color backGroundColor = {14, 24, 51, 255};
const SDL_Color wallColor = {80, 79, 76, 255};
const SDL_Color GREEN = {68, 236, 1, 255};
const SDL_Color BLUE = {20, 224, 252, 255};
const SDL_Color ORANGE = {251, 177, 0, 255};

namespace Log{
  void Notification(std::ostream& os, const std::string &msg);
  void SDLError(std::ostream& os, const std::string &msg);
  void Warning(std::ostream& os, const std::string &msg);
};

namespace Get{
  int xMiddleBar();
  SDL_Rect Bar(double x);
  double Angle(double x, double y);
}

namespace Check{
  bool clickInRect(SDL_MouseButtonEvent e, const SDL_Rect& r);
}

namespace Draw{
  void Rect(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c);
  void Cell(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c);
  void Image(SDL_Renderer *renderer, SDL_Rect r, std::string path);
  void Bar(SDL_Renderer *renderer, double x);

  void destroyImage();
}

#endif // PARAMETER_H_INCLUDED
