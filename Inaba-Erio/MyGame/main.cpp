#include "Engine.h"
#include "testGame.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Inaba::Engine engine(hInstance,640,480);
	engine.Init();
	
	engine._game = new Erio::Game();
	engine.Run();

	delete engine._game;
	engine._game = NULL;
}