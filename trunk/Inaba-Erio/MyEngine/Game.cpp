#include "Game.h"
#include "Scene/Scene.h"
#include "Scene/Import.h"
using namespace Inaba;

Game::Game()
//:_scene(new Scene)
{
}

Game::Game(std::string sceneName)
//:_scene(new Scene)
{
	// otras cosas
	setScene(sceneName);
}

Scene Game::currentScene()
{
	return _scene;
}

void Game::setScene(std::string sceneName)
{
	Import import;
	import.importScene(_scene,sceneName);
	//import scene
}
