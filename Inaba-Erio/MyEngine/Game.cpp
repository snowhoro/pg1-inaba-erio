#include "Game.h"
#include "Scene/Scene.h"
#include "Scene/Import.h"
#include "Renderer\Renderer.h"
using namespace Inaba;

Game::Game()
:_scene(new Scene)
{
}

Game::Game(std::string sceneName)
:_scene(new Scene)
{
	// otras cosas
	//setScene(sceneName,);
}

Game::~Game()
 {
	delete _scene;
	_scene = NULL;
}

Scene Game::currentScene()
{
	return *_scene;
}

void Game::setScene(std::string sceneName, Renderer* renderer)
{
	_scene->deInit();
	Import::importScene(*_scene,sceneName, renderer);
	Init(*renderer);
}
