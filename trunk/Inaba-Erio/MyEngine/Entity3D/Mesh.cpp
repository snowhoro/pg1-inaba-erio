#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include <d3dx9.h>

using namespace Inaba;


Mesh::Mesh(Renderer& pRenderer) : Entity3D(),
_vertex(new ColorVertex[8]),
_renderer(pRenderer)
{

	static const float SIZE = 0.5f;
	_vertex[0].x = -SIZE; _vertex[0].y = SIZE; _vertex[0].z = SIZE;
	_vertex[1].x = SIZE; _vertex[1].y = SIZE; _vertex[1].z = SIZE;
	_vertex[2].x = -SIZE; _vertex[2].y = -SIZE; _vertex[2].z = SIZE;
	_vertex[3].x = SIZE; _vertex[3].y = -SIZE; _vertex[3].z = SIZE;
	_vertex[4].x = -SIZE; _vertex[4].y = SIZE; _vertex[4].z = -SIZE;
	_vertex[5].x = SIZE; _vertex[5].y = SIZE; _vertex[5].z = -SIZE;
	_vertex[6].x = -SIZE; _vertex[6].y = -SIZE; _vertex[6].z = -SIZE;
	_vertex[7].x = SIZE; _vertex[7].y = -SIZE; _vertex[7].z = -SIZE;

	_vertex[0].color = D3DCOLOR_XRGB(255,0,0); 
	_vertex[1].color = D3DCOLOR_XRGB(255,0,0); 
	_vertex[2].color = D3DCOLOR_XRGB(255,0,0);
	_vertex[3].color = D3DCOLOR_XRGB(255,0,0);
	_vertex[4].color = D3DCOLOR_XRGB(255,0,0); 
	_vertex[5].color = D3DCOLOR_XRGB(255,0,0); 
	_vertex[6].color = D3DCOLOR_XRGB(255,0,0);
	_vertex[7].color = D3DCOLOR_XRGB(255,0,0);

	UpdateLocalTransformation();

	_vertexBuffer3D = _renderer.createVertexBuffer3D(sizeof(_vertex), Inaba::ColorVertexType);
    _indexBuffer = _renderer.createIndexBuffer();	
}

Mesh::~Mesh()
{
	if(_vertexBuffer3D){
		delete _vertexBuffer3D;
		_vertexBuffer3D = NULL;
	}
	if(_indexBuffer){
		delete _indexBuffer;
		_indexBuffer = NULL;
	}
}

void Mesh::setData(size_t vertexCount, Inaba::Primitive, const unsigned short* pausIndex, size_t indexCount)
{
	_vertexBuffer3D->setVertexData(_vertex, vertexCount);
	_indexBuffer->setIndexData(pausIndex, indexCount);

}

void Mesh::Draw(Renderer& renderer) const
{
	renderer.setCurrentTexture(NoTexture);
	renderer.Draw(_vertex,Inaba::TriangleStrip, 8);
}
