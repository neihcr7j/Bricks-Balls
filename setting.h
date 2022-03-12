#ifndef SETTING_H
#define SETTING_H

#include <parameter.h>

class Setting{
public:
  const SDL_Rect
    areaBackClient = {WIDTH - WIDTH / 6, HEIGHT - HEIGHT / 10, WIDTH / 6, HEIGHT / 10};

  Setting() {};
  static Setting* Instance()
	{
		if (instance == nullptr) instance = new Setting();
		return instance;
	}

  void running(SDL_Renderer *renderer);

private:
  static Setting* instance;
};

#endif // SETTING_H
