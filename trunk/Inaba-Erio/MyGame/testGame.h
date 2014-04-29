#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "RenderTypes.h"
#include "Quad.h"
#include "Renderer.h"
namespace Erio
{
	//class Quad;
class Game : public Inaba::Game
{
public:
	Game();
	bool Init(Inaba::Renderer&);
	void Frame(Inaba::Renderer&);
	void DeInit();

private:
	Inaba::Quad _quad1;
	Inaba::Quad _quad2;
};

}
#endif