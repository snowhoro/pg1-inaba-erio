#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#include <Windows.h>
#include "myengine_api.h"


namespace Inaba
{
	struct MYENGINE_API ColorVertex
	{
		float x, y, z;
		DWORD color;
	};
	extern const int ColorVertexType;

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
}
#endif