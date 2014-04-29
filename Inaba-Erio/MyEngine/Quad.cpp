#include "Quad.h"
#include "Renderer.h"
#include <d3dx9.h>

using namespace Inaba;

Quad::Quad():
_posX(0.0f),
_posY(0.0f),
_rotation(0.0f),
_scale(1.0f),
_transformationMatrix(new D3DXMATRIX()),
_vertex(new ColorVertex[4])
{
	static const float SIZE = 0.5f;
	_vertex[0].x = -SIZE;	_vertex[0].y = SIZE;	_vertex[0].z = 0.0f;
	_vertex[1].x = SIZE;	_vertex[1].y = SIZE;	_vertex[1].z = 0.0f;
	_vertex[2].x = -SIZE;	_vertex[2].y = -SIZE;	_vertex[2].z = 0.0f;
	_vertex[3].x = SIZE;	_vertex[3].y = -SIZE;	_vertex[3].z = 0.0f;

	_vertex[0].color = D3DCOLOR_XRGB(255,0,0);	
	_vertex[1].color = D3DCOLOR_XRGB(255,0,0);	
	_vertex[2].color = D3DCOLOR_XRGB(255,0,0);
	_vertex[3].color = D3DCOLOR_XRGB(255,0,0);	

	UpdateLocalTransformation();
}

Quad::~Quad()
{
	delete _transformationMatrix;
	_transformationMatrix = NULL;

	delete[] _vertex;
	_vertex = NULL;
}

void Quad::setPos(float posX, float posY)
{
	_posX = posX;
	_posY = posY;

	UpdateLocalTransformation();
}

void Quad::setRotation(float rotation)
{
	_rotation = rotation;

	UpdateLocalTransformation();
}

void Quad::setScale(float scale)
{
	_scale = scale;

	UpdateLocalTransformation();
}

void Quad::Draw(Renderer& renderer) const
{
	renderer.setMatrix(World,_transformationMatrix);
	renderer.Draw(_vertex,Inaba::TriangleStrip, 4);
}

void Quad::UpdateLocalTransformation()
{
	D3DXMATRIX translateMatrix;
	D3DXMatrixTranslation(&translateMatrix, _posX, _posY, 0);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, _rotation);

	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix, _scale, _scale, 1);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&translateMatrix,_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&rotationMatrix,_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix,&scaleMatrix,_transformationMatrix);

}