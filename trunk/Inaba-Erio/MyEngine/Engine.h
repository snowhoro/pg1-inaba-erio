#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include "myengine_api.h"

class Renderer;
class Window;

class MYENGINE_API Engine
{
	private:
		Window *_window;
		Renderer *_renderer;
		int _width;
		int _height;
	public:
		Engine(HINSTANCE, int, int);
		~Engine();
		bool Init();
		void Run();
};
#endif