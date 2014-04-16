#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "RenderTypes.h"
namespace Erio
{

class Game : public Inaba::Game
{
public:
	bool Init(Inaba::Renderer&);
	void Frame(Inaba::Renderer&);
	void DeInit();
private:
	//Inaba::
};

}
#endif