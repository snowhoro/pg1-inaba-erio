#include "AABB.h"

using namespace Inaba;

AABB::AABB()

{
}

AABB::~AABB()
{
}

void AABB::setBounds(TextureCoordVertex* vertices,int numVertex)
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

float AABB::getWidth() {
	return _max.x - _min.x;
}

float AABB::getHeight() {
	return _max.y - _min.y;
}
float AABB::getDepth() {
	return _max.z - _min.z;
}

D3DXVECTOR3 AABB::getCenter(){
	return D3DXVECTOR3((_max.x + _min.x) / 2, (_max.y + _min.y) / 2, (_max.z + _min.z) /2);
}