#ifndef WINDOW_H
#define WINDOW_H
#include "myengine_api.h"
#include <windows.h>
class MYENGINE_API Window
{
	private:
		WNDCLASS wc;
		HINSTANCE hInstance;
		int nCmdShow;
		HWND hwnd;
		WPARAM GetMsg();

	public:
		Window(HINSTANCE,int);
		bool Create(unsigned int, unsigned int);
		void Show();
};

#endif