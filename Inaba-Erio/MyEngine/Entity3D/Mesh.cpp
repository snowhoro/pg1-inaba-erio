#include "Mesh.h"
#include "../Renderer/Renderer.h"
#include <d3dx9.h>
#include "../Physics/Collider.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Physics.h"
using namespace Inaba;

Mesh::Mesh(Renderer& pRenderer) : _renderer(pRenderer){
	_vertexBuffer3D = _renderer.createVertexBuffer3D(sizeof(Inaba::TextureCoordVertex), Inaba::TextureCoordVertexType);
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

void Mesh::setData(const TextureCoordVertex* Tex_Vertex, size_t vertexCount, Inaba::Primitive Prim, const unsigned short* pInt, size_t indexCount)
{
	pPrimitive = Prim;
	_vertexBuffer3D->setVertexData((void*) Tex_Vertex,vertexCount);
	_indexBuffer->setIndexData(pInt,indexCount);

	_vVertex.resize(vertexCount);
	memcpy(&(_vVertex.front()), Tex_Vertex, vertexCount * sizeof(TextureCoordVertex));

	_vIndex.resize(indexCount);
	memcpy(&(_vIndex.front()), pInt, indexCount * sizeof(unsigned short));

	MeshCollider *coll = new MeshCollider();
	coll->build(this);

	getRigidbody()->setCollider(coll);
	getRigidbody()->setHavokMotion(RigidBody::HavokMotion::Dynamic);
	Physics::GetInstance()->addEntity(getRigidbody());

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

const std::vector<TextureCoordVertex>& Mesh::vertexs() const{
	return _vVertex;
}

const std::vector<unsigned short> Mesh::indexs() const{
	return _vIndex;
}