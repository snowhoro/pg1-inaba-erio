#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window w(hInstance,nCmdShow);
	w.Create(640,480);
	w.GetMsg();
}