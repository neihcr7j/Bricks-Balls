#ifndef PLAY_H
#define PLAY_H

#include "level.h"
#include "setting.h"
#include <cstdlib>
#include <ctime>

void unitize(double &x, double &y);

struct Gift{
  int type;
  double x, y;
  const int static speedGift = 5;

  Gift(double _x = 0, double _y = 0, bool _type = 0) : x(_x), y(_y), type(_type) {};
};

struct Ball{
  double x, y;
  double dirX, dirY;
  const int static speedBall = 3;

  Ball(double _x = 0, double _y = 0, double _dirX = 0, double _dirY = 0) : x(_x), y(_y), dirX(_dirX), dirY(_dirY) {};
};

class Play{
public:
  bool flag;
  char a[WIDTH / lCell][HEIGHT / lCell];
  int numbersCell;
  const int static limitNumbersBall = 200;
  std::queue <Ball> setBall;
  std::queue <Gift> setGift;

  Play() : flag(0)
    {
      while (!setBall.empty()) setBall.pop();
      while (!setGift.empty()) setGift.pop();
    };

  static Play* Instance()
	{
		if (instance == nullptr) instance = new Play();
		return instance;
	}

	void start(SDL_Renderer *renderer);
  bool running(SDL_Renderer *renderer);
  void over(SDL_Renderer *renderer);

private:
  bool destroyCell(int i, int j);
  bool checkInCell(double x, double y);
  bool checkX(double x, double y, bool ok);
  bool checkY(double x, double y, bool ok);

  void readLevel(int level);
  void nextBall(Ball &b);
  void openGift(int type);
  void updateBall();
  void updateGift();
  void showCell(SDL_Renderer *renderer);
  void showBall(SDL_Renderer *renderer);
  void showGift(SDL_Renderer *renderer);
  static Play* instance;
};

#endif // PLAY_H
