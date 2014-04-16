#ifndef RENDERER_H
#define RENDERER_H

#include "Vertexbuffer.h"
#include "RenderTypes.h"
#include "myengine_api.h"
#include <windows.h>
#include <d3d9.h>

namespace Inaba
{

class MYENGINE_API Renderer
{
private:
	IDirect3D9 *_d3d;
	IDirect3DDevice9 *_d3ddev;
	Inaba::VertexBuffer *_vertexbuffer;

public:
	Renderer();
	~Renderer();
	bool Init(HWND hwnd);
	void BeginFrame();
	void EndFrame();
	void Draw(const void*,Inaba::Primitive,size_t);
	//IDirect3D9 d3d();
	//IDirect3DDevice9 d3ddev();
};

}
#endif