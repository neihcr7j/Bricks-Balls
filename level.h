#ifndef LEVEL_H
#define LEVEL_H

#include <parameter.h>

class Level{
public:
  const SDL_Rect
    areaBackClient = {WIDTH - WIDTH / 6, HEIGHT - HEIGHT / 10, WIDTH / 6, HEIGHT / 10},
    areaDecLevel = {0, HEIGHT / 3, WIDTH / 3, HEIGHT / 3},
    areaIncLevel = {WIDTH - WIDTH / 3, HEIGHT / 3, WIDTH / 3, HEIGHT / 3};

  int levelMax;
  int numberLevel;
  Level() : numberLevel(0), levelMax(10) {};

  static Level* Instance()
	{
		if (instance == nullptr) instance = new Level();
		return instance;
	}

  void decLevel();
  void incLevel();
  void running(SDL_Renderer *renderer);

private:
  static Level* instance;
};

#endif // LEVEL_H
