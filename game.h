#ifndef GAME_H
#define GAME_H

#include <event.h>

class Game{
private:
  SDL_Window *window;
  SDL_Renderer *renderer;

  bool bRunning;
  int FPS;

  Game(): bRunning(false), window(nullptr), renderer(nullptr), FPS(50) {}

  static Game* instance;

public:
  static Game* Instance()
	{
		if (instance == nullptr) instance = new Game();
		return instance;
	}

	SDL_Renderer *getRenderer() {return renderer;}

  bool init(std::string TITLE, int width, int height);
  bool running();

  double timeForOneFrame();

  void quit();
  void cleaner();
};

#endif // GAMELIB_H_INCLUDED
