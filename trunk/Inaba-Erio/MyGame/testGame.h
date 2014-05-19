#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "RenderTypes.h"
#include "Quad.h"
#include "Renderer.h"
#include "Sprite.h"

namespace Erio
{
	//class Quad;
class Game : public Inaba::Game
{
public:
	Game();
	bool Init(Inaba::Renderer&);
	void Frame(Inaba::Renderer&,Inaba::DirectInput&);
	void DeInit();

private:
	Inaba::Quad _quad1;
	Inaba::Quad _quad2;
	Inaba::Sprite _sprite1; 
};

}
#endif