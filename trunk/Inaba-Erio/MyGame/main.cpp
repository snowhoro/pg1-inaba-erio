#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Inaba::Engine engine(hInstance,640,480);
	engine.Init();
	engine.Run();
}