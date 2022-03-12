#include "play.h"

int unit = 3;

Play* Play::instance = nullptr;

bool Play::destroyCell(int i, int j)
{
  if (a[i][j] == '0') return false;

  if (a[i][j] != '1')
  {
    int r = rand() % 7 + 1;
    if (r == 1) setGift.push(Gift(i * lCell + lCell / 2, (j + 1) * lCell, 0));
    if (r == 2) setGift.push(Gift(i * lCell + lCell / 2, (j + 1) * lCell, 1));
    a[i][j] = '0';
    numbersCell --;
  }

  return true;
}

bool Play::checkInCell(double x, double y)
{
  int i = x / lCell, j = y / lCell;

  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;

  return destroyCell(i, j);
}

bool Play::checkX(double x, double y, bool ok)
{
  if (ok && x + rBall >= WIDTH) return 1;
  if (!ok && x - rBall <= 0) return 1;

  if (y >= yBar && y <= yBar + heightBar)
  {
    if (ok && x + rBall >= Get::xMiddleBar() - widthBar / 2 && x + rBall <= Get::xMiddleBar() - widthBar / 2 + unit) return 1;
    if (!ok && x - rBall <= Get::xMiddleBar() + widthBar / 2 && x - rBall >= Get::xMiddleBar() - widthBar / 2 - unit) return 1;
  }

  if (ok == 0)
  {
    return checkInCell(x - rBall, y);
  }
  else
  {
    return checkInCell(x + rBall, y);
  }
}

bool Play::checkY(double x, double y, bool ok)
{
  if (!ok && y - rBall <= 0) return 1;
  if (ok && y + rBall >= HEIGHT) return 0;
  if (ok && y + rBall >= yBar && y + rBall <= yBar + unit && abs(x - Get::xMiddleBar()) < widthBar / 2) return 1;

  if (ok == 0)
  {
    return checkInCell(x, y - rBall);
  }
  else
  {
    return checkInCell(x, y + rBall);
  }

  return 0;
}

void Play::readLevel(int level)
{
  std::string path = "level/" + std::to_string(level) + ".txt";

  std::ifstream inp(path.c_str());

  numbersCell = 0;

  for (int i = 0; i < HEIGHT / lCell; ++i)
    for (int j = 0; j < WIDTH / lCell; ++j)
    {
      inp >> a[j][i];
      if (a[i][j] != '0' && a[i][j] != '1') numbersCell ++;
    }
}

void Play::nextBall(Ball &b)
{
  bool ok = 1;

  if (b.dirY > 0 && b.y + rBall >= yBar && b.y + rBall <= yBar + unit && abs(b.x - Get::xMiddleBar()) <= widthBar / 2)
  {
    double alpha = acos((b.x - Get::xMiddleBar()) / widthBar);

    b.dirX = cos(alpha);
    b.dirY = -sin(alpha);

    return;
  }

  if (checkX(b.x, b.y, (b.dirX > 0 ? 1 : 0)))
  {
    ok = 0;
    b.dirX = -b.dirX;
  }

  if (checkY(b.x, b.y, (b.dirY > 0 ? 1 : 0)))
  {
    ok = 0;
    b.dirY = -b.dirY;
  }

  if (ok)
  {
    b.x += b.dirX * unit;
    b.y += b.dirY * unit;
  }
}

void Play::openGift(int type)
{
  if (setBall.size() >= limitNumbersBall) return;

  if (type == 0)
  {
    setBall.push(Ball(Get::xMiddleBar(), yBar - rBall, -sqrt(2) / 2, -sqrt(2) / 2));
    setBall.push(Ball(Get::xMiddleBar(), yBar - rBall, 0, -1));
    setBall.push(Ball(Get::xMiddleBar(), yBar - rBall, sqrt(2) / 2, -sqrt(2) / 2));
  }
  else
  {
    int cur = setBall.size();

    while (cur--)
    {
      Ball b = setBall.front();
      setBall.pop();
      setBall.push(b);
      double alpha = Get::Angle(b.dirX, b.dirY);

      setBall.push(Ball(b.x, b.y, cos(alpha + 2 * PI / 3), sin(alpha + 2 * PI / 3)));
      setBall.push(Ball(b.x, b.y, cos(alpha + 4 * PI / 3), sin(alpha + 4 * PI / 3)));
    }
  }
}

void Play::updateBall()
{
  int cur = setBall.size();

  while (cur--)
  {
    Ball b = setBall.front();
    setBall.pop();

    for (int i = 0; i < b.speedBall; ++i)
      nextBall(b);

    if (b.y - rBall < HEIGHT) setBall.push(b);
  }
}

void Play::updateGift()
{
  int cur = setGift.size();

  while (cur--)
  {
    Gift g = setGift.front();
    setGift.pop();

    g.y += g.speedGift;

    if (g.y - rGift >= HEIGHT) continue;

    if (abs(g.x - Get::xMiddleBar() <= rGift + widthBar / 2) && g.y + rGift >= yBar && g.y - rGift <= yBar + heightBar)
      openGift(g.type);
    else
      setGift.push(g);
  }
}

void Play::showCell(SDL_Renderer *renderer)
{
  for (int i = 0; i < WIDTH / lCell; ++i)
    for (int j = 0; j < WIDTH / lCell; ++j)
    {
      SDL_Rect r = {i * lCell, j * lCell, lCell, lCell};

      if (a[i][j] == '1')
        Draw::Cell(renderer, r, wallColor);
      else
      if (a[i][j] == '2')
        Draw::Cell(renderer, r, GREEN);
      else
      if (a[i][j] == '3')
        Draw::Cell(renderer, r, BLUE);
    }
}

void Play::showBall(SDL_Renderer *renderer)
{
  int cur = setBall.size();
  while (cur--)
  {
    Ball b = setBall.front();
//    Draw::Image(renderer, {b.x - rBall, b.y - rBall, 2 * rBall, 2 * rBall}, "image/ball.png");
    Draw::Rect(renderer, {b.x - rBall, b.y - rBall, 2 * rBall, 2 * rBall}, GREEN);
    setBall.pop();
    setBall.push(b);
  }
}

void Play::showGift(SDL_Renderer *renderer)
{
  int cur = setGift.size();
  while (cur--)
  {
    Gift g = setGift.front();
    Draw::Rect(renderer, {g.x - rGift, g.y - rGift, 2 * rGift, 2 * rGift}, (g.type == 0 ? BLUE : ORANGE));
    setGift.pop();
    setGift.push(g);
  }

}

void Play::start(SDL_Renderer *renderer)
{
  if (flag == 0)
  {
    flag = 1;
    readLevel(Level::Instance() -> numberLevel);
  }

  SDL_RenderClear(renderer);
  Draw::Rect(renderer, areaBackGround, backGroundColor);

  showCell(renderer);
  showBall(renderer);
  Draw::Bar(renderer, WIDTH / 2);

  SDL_RenderPresent(renderer);

//  Draw::destroyImage();
}

bool Play::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  Draw::Rect(renderer, areaBackGround, backGroundColor);

  updateBall();
  updateGift();

  showCell(renderer);
  showBall(renderer);
  showGift(renderer);

  Draw::Bar(renderer, Get::xMiddleBar());
  SDL_RenderPresent(renderer);

//  Draw::destroyImage();

  return !(setBall.empty() && numbersCell);
}

void Play::over(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  Draw::Rect(renderer, areaBackGround, backGroundColor);



  SDL_RenderPresent(renderer);
}
