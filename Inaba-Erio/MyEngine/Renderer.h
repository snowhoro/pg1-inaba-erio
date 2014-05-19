#ifndef RENDERER_H
#define RENDERER_H

#include "Vertexbuffer.h"
#include "RenderTypes.h"
#include "xMath.h"
#include "myengine_api.h"
#include <windows.h>
#include <d3d9.h>
#include <iostream>
#include <vector>

namespace Inaba
{

class MYENGINE_API Renderer
{
private:
	IDirect3D9 *_d3d;
	IDirect3DDevice9 *_d3ddev;
	Inaba::VertexBuffer *_vertexbuffer;
	Inaba::VertexBuffer *_textureCoordVertexbuffer;
	std::vector<Texture> _vectorTextures;

public:
	Renderer();
	~Renderer();
	bool Init(HWND hwnd);
	void BeginFrame();
	void EndFrame();
	void Draw(ColorVertex*,Inaba::Primitive,size_t);
	void Draw(TextureCoordVertex*,Inaba::Primitive,size_t);
	void setMatrix(MatrixType, const Matrix&);
	const Texture LoadTexture(const std::string& FileName, int KeyCode);
	void setCurrentTexture (const Texture&);
};

}
#endif