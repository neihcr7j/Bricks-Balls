#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include <parameter.h>

class clientGame{
public:
  const SDL_Rect
    areaPlay = {WIDTH / 2 - WIDTH / 3, HEIGHT / 10, 2 * WIDTH / 3, 2 * HEIGHT / 10},
    areaLevel = {WIDTH / 2 - WIDTH / 3, 4 * HEIGHT / 10, 2 * WIDTH / 3, 2 * HEIGHT / 10},
    areaSetting = {WIDTH / 2 - WIDTH / 3, 7 * HEIGHT / 10, 2 * WIDTH / 3, 2 * HEIGHT / 10};

  clientGame() {};
  static clientGame* Instance()
	{
		if (instance == nullptr) instance = new clientGame();
		return instance;
	}

  void running(SDL_Renderer *renderer);

private:
  static clientGame* instance;
};

#endif // CLIENTGAME_H
