#include "Renderer.h"

Renderer::Renderer():
_d3d(new LPDIRECT3D9()),
_d3ddev(new LPDIRECT3DDEVICE9())
{
}
Renderer::~Renderer()
{
	(*_d3d)->Release();
	delete _d3d;

	(*_d3ddev)->Release();
	delete _d3ddev;
}
bool Renderer::Init(HWND hWnd)
{
	*_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;

    if((*_d3d)->CreateDevice(	D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								hWnd,
								D3DCREATE_SOFTWARE_VERTEXPROCESSING,
								&d3dpp,
								_d3ddev) 
	!= D3D_OK)
		return false;
	return true;
}
void Renderer::BeginFrame()
{
	(*_d3ddev)->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
    (*_d3ddev)->BeginScene();
}
void Renderer::EndFrame()
{
	(*_d3ddev)->EndScene();
    (*_d3ddev)->Present(NULL, NULL, NULL, NULL);
}
LPDIRECT3D9 Renderer::d3d()
{
	return *_d3d;
}
LPDIRECT3DDEVICE9 Renderer::d3ddev()
{
	return *_d3ddev;
}