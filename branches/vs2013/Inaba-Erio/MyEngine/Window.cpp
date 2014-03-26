#include "Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

 switch(message)
 {
   case WM_CLOSE:
     PostQuitMessage(0);
     break;
   default:
     return DefWindowProc(hWnd, message, wParam, lParam);
 }
 return 0;

}
Window::Window(HINSTANCE _hInstance, int _nCmdShow)
{
	hInstance = _hInstance;
	nCmdShow = _nCmdShow;
	wc = {0};
	wc.lpfnWndProc=WndProc;
	wc.hInstance=hInstance;
	wc.hbrBackground=(HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName="myengineWindow";
	bool b = RegisterClass(&wc);
};

bool Window::Create(unsigned int w, unsigned int h)
{
	 hwnd = CreateWindow(wc.lpszClassName,
						"Window Name",
						WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
						0,0,w,h,0,0,hInstance,NULL);
	 if (hwnd == NULL)
	 {
		 return false;
	 }

	 return true;
}
void Window::Show()
{
	ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}
WPARAM Window::GetMsg()
{
	while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}