#include "Engine.h"
#include "Renderer.h"
#include "Window.h"
#include "Game.h"
#include "directinput.h"

using namespace Inaba;
 
Engine::Engine(HINSTANCE hInstance, int width, int height):
_window(new Window(hInstance)),
_renderer(new Renderer),
_directInput(new DirectInput),
_game(NULL),
_width(width),
_height(height)
{
}
Engine::~Engine()
{
	delete _window;
	delete _renderer;
	delete _game;
	delete _directInput;
}
bool Engine::Init()
{
	if(_window->Create(_width,_height) == TRUE 
	   && _renderer->Init(_window->hWnd()) == TRUE
	   && _directInput->init(_window->gethInstance(),_window->hWnd()) == TRUE)
		return true;
	return false;
}
void Engine::Run()
{
	bool GameOn = true;
	MSG msg;
	
	if(!_game)
		return;
	if(!_game->Init(*_renderer))
		return;

	while(GameOn)
	{
		if (_renderer != NULL || _game!= NULL)
		{
			_directInput->reacquire();
			_renderer->BeginFrame();
			_game->Frame(*_renderer, *_directInput);
			_renderer->EndFrame();
		}
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
			GameOn = false;
	}
}