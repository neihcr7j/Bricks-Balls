#include "event.h"

Event* Event::instance = nullptr;

std::string Event::changeType(std::string s)
{
  if (type != "play" && s == "play")
  {
    SDL_ShowCursor(SDL_DISABLE);
  }

  if (type == "play" && s != "play")
  {
    SDL_ShowCursor(SDL_ENABLE);
  }
  return type = s;
}

std::string Event::updating()
{
  SDL_Event e;
  SDL_PollEvent(&e);

  if (e.type == SDL_QUIT)
  {
    return Event::Instance() -> changeType("quit");
  }

  if (e.type == SDL_MOUSEBUTTONDOWN)
  {
    if (Event::Instance() -> type == "client")
    {
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaPlay))
      {
        Ball b(WIDTH / 2, yBar - rBall, 0, 0);
        Play::Instance() -> setBall.push(b);
        return Event::Instance() -> changeType("start");
      }
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaLevel))
      {
        return Event::Instance() -> changeType("level");
      }
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaSetting))
      {
        return Event::Instance() -> changeType("setting");
      }
    }
    else
    if (Event::Instance() -> type == "start")
    {
      double x = e.button.x - WIDTH / 2, y = e.button.y - (yBar - rBall);

      unitize(x, y);

      Ball b = Play::Instance() -> setBall.front();
      Play::Instance() -> setBall.pop();

      b.dirX = x;
      b.dirY = y;

      Play::Instance() -> setBall.push(b);
      return Event::Instance() -> changeType("play");
    }
    else
    if (Event::Instance() -> type == "play")
    {

    }
    else
    if (Event::Instance() -> type == "over")
    {

    }
    else
    if (Event::Instance() -> type == "level")
    {
      if (Check::clickInRect(e.button, Level::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client");
      }
      if (Check::clickInRect(e.button, Level::Instance() -> areaDecLevel))
      {
        Level::Instance() -> decLevel();
        return Event::Instance() -> type;
      }
      if (Check::clickInRect(e.button, Level::Instance() -> areaIncLevel))
      {
        Level::Instance() -> incLevel();
        return Event::Instance() -> type;
      }
    }
    else
    if (Event::Instance() -> type == "setting")
    {
      if (Check::clickInRect(e.button, Setting::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client");
      }
    }
  }


  return Event::Instance() -> type;
}
