#include "Engine.h"
#include "testGame.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Inaba::Engine engine(hInstance,800,600);

	engine.Init();
	engine._game = new Erio::Game();
	engine.Run();
}