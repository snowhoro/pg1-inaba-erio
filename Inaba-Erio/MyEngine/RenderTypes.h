#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#include <Windows.h>
#include "myengine_api.h"
#include <d3d9.h>

namespace Inaba
{
	struct MYENGINE_API ColorVertex
	{
		float x, y, z;
		DWORD color;
	};
	extern const DWORD ColorVertexType;

	struct MYENGINE_API TextureCoordVertex
	{
		float x, y, z;
		float u, v;
	};

	extern const int TextureCoordVertexType;

	enum Primitive
	{
		TriangleList = 0,
		TriangleStrip,
		PointList,
		LineList,
		LineStrip,
		TriangleFan,
		PrimitiveCount
	};

	enum MatrixType
	{
		View = 0,
		Projection,
		World,
		MatrixTypeCount
	};

	typedef IDirect3DTexture9 *Texture;
	static const Texture NoTexture = NULL;
}
#endif