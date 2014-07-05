#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "RenderTypes.h"
#include "Quad.h"
#include "Renderer.h"
#include "Sprite.h"
#include "timer.h"
#include "Animation.h"
namespace Erio
{
	//class Quad;
class Game : public Inaba::Game
{
public:
	Game();
	bool Init(Inaba::Renderer&);
	void Frame(Inaba::Renderer&,Inaba::DirectInput&, Inaba::Timer&);
	void DeInit();

private:
	Inaba::Quad _quad1;
	Inaba::Quad _quad2;
	Inaba::Sprite _sprite1; 
	Inaba::Animation _anim1;
};

}
#endif