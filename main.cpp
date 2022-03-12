#include "game.h"

int main( int argc, char * argv[] )
{
  srand(time(nullptr));

  int frameStart, frameTime;
  Log::Notification(std::cout, "Game init attempt....");

  if (Game::Instance() -> init(TITLE, WIDTH, HEIGHT))
  {
    Log::Notification(std::cout, "Game init success!");
    while(Game::Instance() -> running())
    {
      frameStart = SDL_GetTicks();

      std::string type = Event::Instance() -> updating();

      if (type == "client")
      {
        clientGame::Instance() -> running(Game::Instance() -> getRenderer());
      }
      else
      if (type == "quit")
      {
        Game::Instance() -> quit();
      }
      else
      if (type == "start")
      {
        Play::Instance() -> start(Game::Instance() -> getRenderer());
      }
      else
      if (type == "play")
      {
        if (!Play::Instance() -> running(Game::Instance() -> getRenderer())) Event::Instance() -> changeType("over");
      }
      else
      if (type == "over")
      {
        Play::Instance() -> over(Game::Instance() -> getRenderer());
      }
      else
      if (type == "level")
      {
        Level::Instance() -> running(Game::Instance() -> getRenderer());
      }
      else
      if (type == "setting")
      {
        Setting::Instance() -> running(Game::Instance() -> getRenderer());
      }

      frameTime = SDL_GetTicks() - frameStart;
      if (frameTime < Game::Instance() -> timeForOneFrame())
      {
        SDL_Delay(int(Game::Instance() -> timeForOneFrame() - frameTime));
      }
    }
  }

  Game::Instance() -> cleaner();
  Log::Notification(std::cout, "game closing.....");

  return 0;
}

