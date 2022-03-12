#ifndef EVENT_H
#define EVENT_H

#include "clientGame.h"
#include "play.h"

class Event{
public:
  std::string type;

  static Event* Instance()
	{
		if (instance == nullptr) instance = new Event();
		return instance;
	}

  std::string changeType(std::string s);
  std::string updating();

private:
  Event(): type("client") {};
  static Event* instance;
};

#endif // EVENT_H
