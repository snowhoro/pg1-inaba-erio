#include "Engine.h"
#include "Renderer.h"
#include "Window.h"

Engine::Engine(HINSTANCE hInstance, int width, int height):
_window(new Window(hInstance)),
_renderer(new Renderer),
_width(width),
_height(height)
{
}
Engine::~Engine()
{
	delete _window;
	delete _renderer;
}
bool Engine::Init()
{
	if(_window->Create(_width,_height) == TRUE 
	   && _renderer->Init(_window->hWnd()) == TRUE)
		return true;
	return false;
}
void Engine::Run()
{
	bool GameOn = true;
	MSG msg;
	
	while(GameOn)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
			GameOn = false;

		_renderer->BeginFrame();
		_renderer->EndFrame();
	}
}