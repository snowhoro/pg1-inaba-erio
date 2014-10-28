#include "AABB.h"

using namespace Inaba;

AABB::AABB()

{
}

AABB::~AABB()
{
}

void AABB::setBound(TextureCoordVertex* vertices,int numVertex)
{
	_min = *vertices;
	_max = _min;
	

	for(int i = 1; i < numVertex; i++)
	{
		if(vertices[i].x < _min.x)
			_min.x = vertices[i].x;
		if(vertices[i].y < _min.y)
			_min.y = vertices[i].y;
		if(vertices[i].z < _min.z)
			_min.z = vertices[i].z;

		if(vertices[i].x > _max.x)
			_min.x = vertices[i].x;
		if(vertices[i].y > _max.y)
			_min.y = vertices[i].y;
		if(vertices[i].z > _max.z)
			_min.z = vertices[i].z;
	}
}