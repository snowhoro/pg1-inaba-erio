#ifndef ENGINE_H
#define ENGINE_H

#include <windows.h>
#include "myengine_api.h"

namespace Inaba
{

class Renderer;
class Window;
class Game;
class MYENGINE_API Engine
{
	private:
		Window *_window;
		Renderer *_renderer;
		//Game *_game;
		int _width;
		int _height;
	public:
		Engine(HINSTANCE, int, int);
		~Engine();
		bool Init();
		void Run();
		Game *_game;
};

}
#endif