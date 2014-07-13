#include "Game.h"
#include "Scene/Scene.h"
#include "Scene/Import.h"
#include "Renderer\Renderer.h"
using namespace Inaba;

Game::Game()
:_currentScene(NULL)
{
}

Game::Game(std::string sceneName)
:_currentScene(NULL)
{
	// otras cosas
	//setScene(sceneName,);
}

Game::~Game()
 {
	delete _currentScene;
	_currentScene = NULL;
}

Scene* Game::currentScene()
{
	return _currentScene;
}

void Game::setScene(std::string sceneName, Renderer* renderer)
{
	if(_currentScene)
		_currentScene->deInit();

	if(_scenes.empty())
		return;
		
	for(int i = 0; i < _scenes.size(); i++)
	{
		if(_scenes[i]->Name() == sceneName)
			_currentScene = _scenes[i];
	}

	if(!_currentScene)
		return;

	Import::GetInstance()->importScene(*_currentScene);
	_currentScene->Init(*renderer);
}

void Game::AddScene(Scene* scene)
{
	_scenes.push_back(scene);
}
