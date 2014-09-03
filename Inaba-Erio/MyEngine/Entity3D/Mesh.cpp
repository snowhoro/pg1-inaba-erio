#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include <d3dx9.h>

using namespace Inaba;

Mesh::Mesh(Renderer& pRenderer) : _renderer(pRenderer){
	_vertexBuffer3D = _renderer.createVertexBuffer3D(sizeof(Inaba::ColorVertex), Inaba::ColorVertexType);
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

void Mesh::setData(const ColorVertex* Tex_Vertex, size_t vertexCount, Inaba::Primitive Prim, const unsigned short* pInt, size_t indexCount)
{
	pPrimitive = Prim;
	_vertexBuffer3D->setVertexData((void*) Tex_Vertex,vertexCount);
	_indexBuffer->setIndexData(pInt,indexCount);

}

void Mesh::Draw(Renderer& renderer) const{
	_vertexBuffer3D->bind();
	_indexBuffer->bind();
	renderer.setCurrentTexture(NoTexture);
	renderer.setMatrix(World,_transformationMatrix);
	renderer.Draw(pPrimitive);
}

void Mesh::Update(Timer&)
{

}