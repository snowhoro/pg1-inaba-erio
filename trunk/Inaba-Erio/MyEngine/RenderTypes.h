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
	extern const DWORD ColorVertexType;

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
}
#endif