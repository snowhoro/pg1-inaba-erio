#include "Renderer.h"

using namespace Inaba;
 
D3DPRIMITIVETYPE primitivesMapping[Inaba::PrimitiveCount] =
{
	D3DPT_TRIANGLELIST, 
	D3DPT_TRIANGLESTRIP,
	D3DPT_POINTLIST,
	D3DPT_LINELIST,     
	D3DPT_LINESTRIP,
	D3DPT_TRIANGLEFAN
};

Renderer::Renderer():
_d3d(NULL),
_d3ddev(NULL),
_vertexbuffer(NULL)
{
}
Renderer::~Renderer()
{
	_d3d->Release();
	delete _d3d;
	_d3ddev->Release();
	delete _d3ddev;
}
bool Renderer::Init(HWND hWnd)
{
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;

    if(_d3d->CreateDevice(	D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							hWnd,
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&d3dpp,
							&_d3ddev) 
	== D3D_OK)
	{
		_vertexbuffer = new Inaba::VertexBuffer(_d3ddev,sizeof(Inaba::ColorVertex),Inaba::ColorVertexType);
		return true;
	}
	return false;
}
void Renderer::BeginFrame()
{
	_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    _d3ddev->BeginScene();
}
void Renderer::EndFrame()
{
	_d3ddev->EndScene();
    _d3ddev->Present(NULL, NULL, NULL, NULL);
}
void Renderer::Draw(const void* vertex,Inaba::Primitive primitive,size_t vertexCount)
{
	_vertexbuffer->bind();
	_vertexbuffer->draw(vertex,primitivesMapping[primitive], vertexCount);
}
/*LPDIRECT3D9 Renderer::d3d()
{
	return *_d3d;
}
LPDIRECT3DDEVICE9 Renderer::d3ddev()
{
	return *_d3ddev;
}*/