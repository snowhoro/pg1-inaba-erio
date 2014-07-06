#ifndef GAME_H
#define GAME_H

#include "myengine_api.h"
#include <string>

namespace Inaba
{

class DirectInput;
class Renderer;
class Timer;
class Scene;

class MYENGINE_API Game
{
public:
	Game();
	Game(std::string);
	virtual bool Init(Inaba::Renderer&) = 0;
	virtual void Frame(Inaba::Renderer&, Inaba::DirectInput&, Inaba::Timer&) = 0;
	virtual void DeInit() = 0;
	Scene currentScene();
	void setScene(std::string);
private:
	Scene *_scene;

};

}
#endif