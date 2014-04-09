#ifndef RENDERER_H
#define RENDERER_H

#include <windows.h>
#include <d3d9.h>
class Renderer
{
private:
	LPDIRECT3D9 *_d3d;
	LPDIRECT3DDEVICE9 *_d3ddev;
public:
	Renderer();
	~Renderer();
	bool Init(HWND hwnd);
	void BeginFrame();
	void EndFrame();
	LPDIRECT3D9 d3d();
	LPDIRECT3DDEVICE9 d3ddev();
};
#endif