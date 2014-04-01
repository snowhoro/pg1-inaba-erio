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
Window::Window(int _nCmdShow)
{
	nCmdShow = _nCmdShow;
	wc = {0};
	wc.lpfnWndProc=WndProc;
	wc.hInstance=GetModuleHandle(NULL);
	wc.hbrBackground=(HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName="myengineWindow";
};

bool Window::Create(unsigned int width, unsigned int height)
{

	if (!RegisterClass(&wc)){
		return false;
		//Error al registrar la clase window
	}
	hwnd = CreateWindow(
		wc.lpszClassName,					//LPCTSTR lpClassName
		"Window",							//LPCTSTR lpWindowName
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//DWORD dwStyle
		0,									//int X
		0,									//INT Y
		width,								//int nWidth
		height,							//int nHeight
		0,									//HWND hWndParent
		0,									//HMENU hMenu
		GetModuleHandle(NULL),				//HINSTANCE hInstance
		NULL								//LPVOID lpParam
		);
						
	 if (hwnd != NULL)
	 {
		 GetMsg();
		 return true;
	 }

	 return false;
}
void Window::Show()
{
	ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}
WPARAM Window::GetMsg()
{
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}