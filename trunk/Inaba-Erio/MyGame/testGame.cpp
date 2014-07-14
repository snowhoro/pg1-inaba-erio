#include "testGame.h"
#include "Input/directinput.h"
#include "Entity2D\Sprite.h"
#include "Scene1.h"
#include "Scene2.h"
using namespace Erio;

Game::Game()
: Inaba::Game()
{
}

bool Game::Init(Inaba::Renderer& renderer)
{
	scene1 = new Scene1(this);
	AddScene(scene1);
	setScene("scene1", &renderer);

	scene2 = new Scene2(this);
	AddScene(scene2);
	return true;
}

void Game::Frame(Inaba::Renderer& renderer, Inaba::DirectInput& directInput, Inaba::Timer& timer)
{
	currentScene()->Frame(renderer, directInput ,timer);
}

void Game::DeInit()
{
}