#ifndef WINDOW_H
#define WINDOW_H
#include "myengine_api.h"
#include <windows.h>
class MYENGINE_API Window
{
	private:
		MSG msg;        
		WNDCLASS wc;
		HINSTANCE hInstance;
		int nCmdShow;
		HWND hwnd;

	public:
		Window(HINSTANCE,int);
		bool Create(unsigned int, unsigned int);
		void Show();
		WPARAM GetMsg();
};

#endif