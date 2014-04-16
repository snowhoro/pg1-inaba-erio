#ifndef GAME_H
#define GAME_H

#include "myengine_api.h"

namespace Inaba
{

class Renderer;

class MYENGINE_API Game
{
public:
	Game();
	virtual bool Init(Inaba::Renderer&) = 0;
	virtual void Frame(Inaba::Renderer&) = 0;
	virtual void DeInit() = 0;
};

}
#endif