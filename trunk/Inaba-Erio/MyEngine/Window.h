#ifndef WINDOW_H
#define WINDOW_H
#include "myengine_api.h"
#include <windows.h>
class MYENGINE_API Window
{
	private:
		int nCmdShow;
		WNDCLASS wc;
		HWND hwnd;
		WPARAM GetMsg();

	public:
		Window(int nCmdShow); // Constructor 
		bool CreateWnd(unsigned int width, unsigned int height);
		void Show();
};

#endif